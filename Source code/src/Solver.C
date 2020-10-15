///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.4                         //
//  Year   : 2019                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
///////////////////////////////////////////

/// Solver
/// This a namespace collecting all the solvers
/// for ODEs and PDEs used in SCIANTIX.
/// In general, the ODEs and PDEs are solved
/// by the Backward Euler (BE) method.
/// For non-linear problems, BE is paired
/// with Newton method.

#include <iostream>
#include "Solver.h"
#include "GlobalVariables.h"
using namespace std;

namespace Solver
{
  // Integrator
  // Solver for the ODE [y' = + S]
  double Integrator(double initial_condition, double source_term, double time_step)
  {
    return initial_condition + source_term * time_step;
  }

  // Decay
  // Solver for the ODE [y' = - L y + S]
  double Decay(double initial_condition, double decay_rate, double source_term, double time_step)
  {
    return (initial_condition + source_term * time_step) / (1.0 + decay_rate * time_step);
  }

  // BinaryInteraction
  // Sovler for the ODE [y' = -k y**2]
  double BinaryInteraction(double initial_condition, double interaction_coefficient, double time_step)
  {
    return Decay(initial_condition, interaction_coefficient * initial_condition, 0.0, time_step);
  }

  // LimitedGrowth
  // Solver for the ODE [y' = k / y + S]
  double LimitedGrowth(double initial_condition, double growth_rate, double source_term, double time_step)
  {
    return 0.5 * ((initial_condition + source_term * time_step) + sqrt(pow(initial_condition + source_term * time_step, 2) + 4.0 * growth_rate * time_step));
  }

  // SpectralDiffusion
  // Solver for the spatially averaged solution of the PDE [dy/dt = D div grad y + S]
  // We apply a spectral approach in space, projecting the equation on the eigenfunctions of the laplacian operator.
  // We use the first order backward Euler solver in time.
  // The number of terms in the expansion, N, is fixed a priori.
  double SpectralDiffusion(std::vector<double>& initial_condition, int N, double diffusion_coefficient, double domain_radius, double source_term, double time_step)
  {
    unsigned short int n(0);
    unsigned short int np1(1);

    double diffusion_rate_coeff(0.0);
    double diffusion_rate(0.0);
    double source_rate_coeff(0.0);
    double source_rate(0.0);
  	std::vector<double> time_coefficient(N, 0.0);
	  double projection_coeff(0.0);
	  double solution(0.0);

    diffusion_rate_coeff = pow(Pi, 2) * diffusion_coefficient / pow(domain_radius, 2);
    projection_coeff = - 2.0 * sqrt(2.0 / Pi);
    source_rate_coeff = projection_coeff * source_term;

    for (n = 0; n < N; n++)
    {
      np1 = n + 1;
      const double n_coeff = pow(- 1.0, np1) / np1;

      diffusion_rate = diffusion_rate_coeff * pow(np1, 2);
      source_rate = source_rate_coeff * n_coeff;

      time_coefficient[n] = Solver::Decay(initial_condition[n], diffusion_rate, source_rate, time_step);
      initial_condition[n] = time_coefficient[n];

      solution += projection_coeff * n_coeff * time_coefficient[n] / ((4./3.) * Pi);
    }

    return solution;
  }

  // FORMAS
  // Solver for the spatially average solution of the PDE [dy/dt = D div grad y + S]
  // designed for time-varying conditions [1,2]
  // [1] Forsberg and Massih, Journal of Nuclear Materials, 127 (1985) 141-145
  // [2] Lassmann and Benk, Journal of Nuclear Materials, 280 (2000) 127-135
  double FORMAS(double initial_condition[], double diffusion_coefficient, double domain_radius, double source_term, double time_step)
  {
    // Constants derived from a priori linear approximation of the diffusion kernel
    // Some are not needed and reported for the sake of completeness
    //const double a_coeff[4];
    //a_coeff[0] = 0.2315450;
    //a_coeff[1] = 0.0948453;
    //a_coeff[2] = 0.0282898;
    //a_coeff[3] = 0.6453200;

    double b_coeff[4];
    b_coeff[0] = 72.5968;
    b_coeff[1] = 796.773;
    b_coeff[2] = 29083.0;
    b_coeff[3] = 10.2469;

    double a_over_b[4];
    a_over_b[0] = 3.18947e-03;
    a_over_b[1] = 1.19037e-04;
    a_over_b[2] = 9.72726e-07;
    a_over_b[3] = 6.29771e-02;

    // Non-dimensional (diffusion) time
    const double dtau = time_step * diffusion_coefficient / pow(domain_radius, 2);

    double term[4];
    double t1 = 0.0;
    for (int n = 0; n < 4; n++)
    {
      double arg = b_coeff[n] * dtau;
      if (arg < 1.0e-04)
        term[n] = - arg;
      else if (arg > 70.0)
        term[n] = - 1.0;
      else
        term[n] = exp(- arg) - 1.0;

      t1 += term[n] * a_over_b[n];
    }

    double t2 = 0.0;
    if (dtau < 0.1)
      t2 = 2.25675833 * pow(dtau, 1.5) - 1.5 * pow(dtau, 2);
    else
      t2 = dtau - 0.06159589 * (1.0 - exp( -9.86960440 * dtau));

    // Non-dimensional source
    if (abs(t2-t1) > 1.0e-15)
    {
    	const double source = source_term * time_step / (t2 - t1);

    	for (int n = 0; n < 4; n++)
    	{
    		initial_condition[n] += term[n] * (initial_condition[n] - source * a_over_b[n]);
		}
	}

    return (initial_condition[0] + initial_condition[1] + initial_condition[2] + initial_condition[3]);
  }

  /// Conjugate Gradient method
  /// Solver for NxN linear systems of algebraic equations.
  /// Can handle non-symmetric matrix, but may struggle with high condition numbers
  /// The matrix of coefficients (A) must be passed as a row array of length N*N
  /// The solution is returned via the input RHS b
  /// Default tolerance on the residual norm is set to 1e-6

  void ConjugateGradient(int N, double A[], double b[])
  {
    double err(0.0);
    double tol(1.0e-06);
    int k,n,m;
    const int K(50);
    double x[N]; // solution
    double r[N]; // residual
    double p[N]; // direction
    double norm(0.0); // norm of p in A-space
    double alfa(0.0); // updater of solution
    double beta(0.0); // updater of direction

    /*NB: discarding A[N][N] for A[N*N] means traducing every double loop on the matrix like:
    for(n=0;n<N;n++){
      r[n] = 0.0;
      for(m=0;m<N;m++) r[n] += AA[n][m] * x[m];
    }
    into:
    for(n=0;n<N;n++){
      r[n] = 0.0;
      for(m=0;m<N;m++) r[n] += AA[m+n*N] * x[m];
    }*/

    // Cast transposed matrix
    double A_T[N*N];
    for (n=0; n<N;++n) for (m=0; m<N; ++m) A_T[m+n*N]=A[n+N*m];

    // Cast new matrix AA=A^T*A and new solution vector bb=A^T*b
    double AA[N*N];
    double bb[N];

    for (n=0; n<N;++n){
      for (m=0; m<N; ++m){
         AA[m+n*N] = 0.;
         for (unsigned short int k=0; k<N; ++k) AA[m+n*N] += A_T[k+n*N]*A[m+k*N];
      }
    }
    for (n=0; n<N;++n){
      bb[n] = 0.;
      for (unsigned short int k=0; k<N; ++k) bb[n] += A_T[k+n*N]*b[k];
    }

    for(n=0;n<N;n++) x[n] = 1.0;//bb[n];
    for(n=0;n<N;n++){
      r[n] = 0.0;
      for(m=0;m<N;m++) r[n] += AA[m+n*N] * x[m];
      r[n] = bb[n] - r[n];
    }
    for(n=0;n<N;n++) p[n] = r[n];
    for(k=0;k<K;k++){
      norm = 0.0; alfa = 0.0; beta = 0.0; err = 0.0;
      for(n=0;n<N;n++) for(m=0;m<N;m++) norm += p[n] * AA[m+n*N] * p[m];
      for(n=0;n<N;n++) alfa += p[n] * r[n]; alfa /= norm;
      for(n=0;n<N;n++) x[n] = x[n] + alfa * p[n];
      for(n=0;n<N;n++){
        r[n] = 0.0;
        for(m=0;m<N;m++) r[n] += AA[m+n*N] * x[m];
        r[n] = bb[n] - r[n];
      }
      for(n=0;n<N;n++) for(m=0;m<N;m++) beta += p[n] * AA[m+n*N] * r[m]; beta /= norm;
      for(n=0;n<N;n++) p[n] = r[n] - beta * p[n];
      for(n=0;n<N;n++) err += r[n] * r[n]; err = sqrt(err); if(err < tol) break;
    }
    //cast solution
    for(n=0;n<N;n++) b[n] = x[n];
  }

  /// Preconditioned BiConjugate Gradient method (PBCG)
  /// Solver for NxN linear systems of algebraic equations, can handle non-symmetric matrix
  /// The matrix of coefficients (A) must be passed as a row array of length N*N
  /// The solution is returned via the input RHS b
  /// Default tolerance on the residual norm is set to 1e-6
  /// In this version, the preconditioner is chosen as the diagonal of the input matrix
  /// Please note that pivoting is not enforced, hence breakdown arises if zero elements
  /// are found in pivotal positions when the preconditioner is casted.

  void PBiCG(int N, double A[], double b[])
  {
    double x[N]; //solution
    int n,m,k;  //support index
    const int K(2*N); // maximum number of iterations
    double r[N], r_star[N]; //residuals
    double alfa(0.), beta(0.); //projectors
    double beta_factors[2]={0.,0.}; // support bins to store quantities useful for beta and alfa calculation
    double p[N], p_star[N], z[N], z_star[N], q[N], q_star[N]; // directions
    double M[N*N]; //preconditioner
    double A_T[N*N]; //input matrix transposed
    double err(0.), tol(1.e-20);

    //cast preconditioner (here, trivial diagonal of the input matrix)
    for(n=0;n<N*N; ++n) M[n] = 0.; for(n=0;n<N; ++n) M[n+N*n] = A[n+N*n];
    //cast inverse preconditioner (need to check if some diagonal entries are zero!)
    for(n=0;n<N; ++n) M[n+N*n]=1.0/M[n+N*n];
    //cast transposed matrix
    for(n=0;n<N; ++n) for(m=0;m<N; ++m) A_T[N*n+m] = A[N*m+n];
    //guess initial solution
    for(n=0;n<N; ++n) x[n] = 1.0;//b[n];
    //evaluate initial residuals and cnj residuals
    for(n=0;n<N; ++n){
      r[n] = 0.;
      for(m=0;m<N; ++m) r[n] += A[m+N*n]*x[m];
      r[n] = b[n] - r[n];
      r_star[n] = r[n];
    }
    //main loop beginning---
    for(k=0;k<K; ++k){
      err = 0.;
      beta_factors[0] = beta_factors[1]; //store previous iteration values
      beta_factors[1] = 0.;
      //solve systems for (preconditioned) biconjugate directions updating
      for(n=0;n<N; ++n){
        z[n] = M[n+N*n] * r[n];
        z_star[n] = M[n+N*n] * r_star[n]; //with diagonal precondioner, (M and M^T) ^-1 are the same
      }
      // update orthogonal projector beta
      for(n=0;n<N; ++n) beta_factors[1] += z[n]*r_star[n]; //if (std::abs(beta_factors[1]) <= 1.e-35) {std::cout<< "BREAKDOWN!"; return;}
      //update directions
      if (k != 0){
        beta = beta_factors[1]/beta_factors[0];
        for(n=0;n<N; ++n){
          p[n] = z[n] + beta * p[n];
          p_star[n] = z_star[n] + beta * p_star[n];
        }
      } else{
        for(n=0;n<N; ++n){
          p[n] = z[n];
          p_star[n] = z_star[n];
        }
      }
      for(n=0;n<N; ++n){
        q[n] = 0.;
        q_star[n] = 0.;
        for(m=0;m<N; ++m){
          q[n] += A[m+N*n]*p[m];
          q_star[n] += A_T[m+N*n]*p_star[m];
        }
      }
      alfa = 0.;
      //update orthogonal projector alfa
      for(n=0;n<N; ++n) alfa += p_star[n]*q[n];
      alfa = beta_factors[1] / alfa;
      //update solution and residuals
      for(n=0;n<N; ++n){
        x[n] += alfa * p[n];
        r[n] -= alfa * q[n];
        r_star[n] -= alfa * q_star[n];
      }
      //check for convergence
      for(n=0;n<N; ++n) err += r[n]*r[n]; err=std::sqrt(err); if (err<tol) break;
    } //main loop end---
    //cast solution
    for(n=0;n<N; ++n) b[n] = x[n];
  }

  /// Preconditioned BiConjugate Gradient STABilized method (PBCGSTAB)
  /// Solver for NxN linear systems of algebraic equations, can handle non-symmetric matrix
  /// The matrix of coefficients (A) must be passed as a row array of length N*N
  /// The solution is returned via the input RHS b
  /// Default tolerance on the residual norm is set to 1e-6
  /// In this version, the preconditioner is chosen as the diagonal of the input matrix
  /// Please note that pivoting is not enforced, hence breakdown arises if zero elements
  /// are found in pivotal positions when the preconditioner is casted.
  /// More robust and faster convergence than PBCG.
  /// Ref.: H.A. Van der Vorst,Bi-CGSTAB: A Fast and Smoothly Converging Variant of Bi-CG for the Solution
  /// of Nonsymmetric Linear Systems, SIAM J. Sci. and Stat. Comput. 13 (2), 1992.

  void PBiCGSTAB(int N, double A[], double b[])
  {
    double x[N]; //solution
    int n,m,k;  //support index
    const int K(50); // maximum number of iterations
    double r[N], r_star[N]; //residuals
    double alfa(0.), beta(0.), dumper(0.); //projectors+dumper
    double beta_factors[2]; // support bins to store quantities useful for beta and alfa calculation
    double p[N], p_star[N], q[N]; // directions
    double v[N], w[N], w_star[N]; //directions
    double M[N*N]; //preconditioner
    //double A_T[N*N]; //input matrix transposed
    double err(0.), tol(1.e-6), num(0.), den(0.);

    //cast preconditioner (here, trivial diagonal of the input matrix)
    for(n=0;n<N*N; ++n) M[n] = 0.; for(n=0;n<N; ++n) M[n+N*n] = A[n+N*n];
    //cast inverse preconditioner (need to check if some diagonal entries are zero!)
    for(n=0;n<N; ++n) M[n+N*n]=1.0/M[n+N*n];
    //cast transposed matrix
    //for(n=0;n<N; ++n) for(m=0;m<N; ++m) A_T[N*n+m] = A[N*m+n];
    //guess initial solution
    for(n=0;n<N; ++n) x[n] = 1.0;//b[n];
    for(n=0;n<N; ++n){
      r[n] = 0.;
      v[n] = 0.;
      for(m=0;m<N; ++m) r[n] += A[m+N*n]*x[m];
      r[n] = b[n] - r[n];
      r_star[n] = r[n]; //in the stabilized method, this is never updated!
    }
    beta_factors[0] = beta_factors[1] = 1.;
    alfa = dumper = 1.;
    //main loop beginning---
    for(k=0;k<K; ++k){
      err = 0.; num=0.; den=0.;
      beta_factors[0] = beta_factors[1]; //store previous iteration values
      beta_factors[1] = 0.;
      // update orthogonal projector beta
      for(n=0;n<N; ++n) beta_factors[1] += r_star[n]*r[n]; //if (std::abs(beta_factors[1]) <= 1.e-35) {std::cout<< "BREAKDOWN!"; return;}
      //update directions
      if (k != 0){
        beta = beta_factors[1]/beta_factors[0] * alfa / dumper; //this alfa comes from previous iteration
        for(n=0;n<N; ++n){
          p[n] = r[n] + beta * (p[n] - dumper * v[n]); //kind of weighted sum of current and old direction
        }
      } else for(n=0;n<N; ++n) p[n] = r[n];
      //solve system
      for(n=0;n<N; ++n) p_star[n] = M[n+N*n] * p[n];

      for(n=0;n<N; ++n){
        v[n] = 0.;
        for(m=0;m<N; ++m) v[n] += A[m+N*n]*p_star[m];
      }
      alfa = 0.;
      for(n=0;n<N; ++n) alfa += r_star[n] * v[n];
      alfa = beta_factors[1] / alfa;
      for(n=0;n<N; ++n) w[n] = r[n] - alfa * v[n];
      for(n=0;n<N; ++n) err += w[n]*w[n]; err=std::sqrt(err);
      if (err<tol){
        for(n=0;n<N; ++n) x[n] += alfa * p_star[n];
        break;
      }

      for(n=0;n<N; ++n) w_star[n] = M[n+N*n] * w[n];
      for(n=0;n<N; ++n){
        q[n] = 0.;
        for(m=0;m<N; ++m) q[n] += A[m+N*n]*w_star[m];
      }
      for(n=0;n<N; ++n){
        num += q[n]*w[n];
        den += q[n]*q[n];
      }
      dumper = num/den;
      for(n=0;n<N; ++n){
        x[n] += alfa * p_star[n] + dumper * w_star[n];
        r[n] = w[n] - dumper * q[n];
      }
      //check for convergence
      err= 0.;
      for(n=0;n<N; ++n) err += r[n]*r[n]; err=std::sqrt(err); if (err<tol) break;
    }//main loop end---
    //cast solution
    for(n=0;n<N; ++n) b[n] = x[n];
  }

  /// LU decomposition, Doolittle algorithm, according to Dahlquist, Germund, Ake Bjorck & Anderson, Ned,
  /// Numerical Methods, Prentice Hall, 1974
  /// The function performs firstly the LU decomposition of the input matrix,
  /// storing in it the lower and upper matrixes; then, the system solution is
  /// accomplished using the factorized matrix and a backward substitution method.
  /// The solution is stored and returned in the rhs vector b.
  /// NB: this function can be used also to perform only the decomposition itslef (ie for preconditioning)
  /// passing a dummy rhs.

  void LUGauss(int N, double * A, double * b)
  {
    int i, j, k, l;
    double sum(0.), y[N];

    // decomposition--
    for(k=0;k<N;++k){
       for(j=k;j<N;++j){
          sum=0.;
          for(l=0;l<k;++l)sum+=A[k*N+l]*A[l*N+j];
          A[k*N+j]=A[k*N+j]-sum;
        }
       for(i=k+1;i<N;++i){
          sum=0.;
          for(l=0;l<k;++l)sum+=A[i*N+l]*A[l*N+k];
          A[i*N+k]=(A[i*N+k]-sum)/A[k*N+k];
       }
     } // end decomposition--

    // system solution--
    for(i=0;i<N;++i){
       sum=0.;
       for(k=0;k<i;++k)sum+=A[i*N+k]*y[k];
       y[i]=b[i]-sum;
       b[i] = 0.; // to cast solution in the input array b, first set this = 0
    }
    for(i=N-1;i>=0;--i){
       sum=0.;
       for(k=i+1;k<N;++k) sum+=A[i*N+k]*b[k];
       b[i]=(y[i]-sum)/A[i*N+i];
    } // end system solution --
  }

  //The function solve a system of two linear equations according to Cramer method.
  void Laplace2x2(double A[], double b[])
  {
    double detX(0.0), detY(0.0);
    double detA = A[0]*A[3] - A[1]*A[2];

    if (detA != 0.0)
    {
      detX = b[0]*A[3] - b[1]*A[1];
      detY = b[1]*A[0] - b[0]*A[2];
      b[0] = detX / detA;
      b[1] = detY / detA;
    }
  }

  //The function solve a system of three linear equations according to Cramer method.
  void Laplace3x3(double A[], double b[])
  {
    double detX(0.0), detY(0.0), detZ(0.0);
    double detA = A[0]*(A[4]*A[8]-A[5]*A[7]) - A[1]*(A[3]*A[8]-A[5]*A[6]) + A[2]*(A[3]*A[7]-A[4]*A[6]);

  if (detA != 0.0)
    {
      detX = b[0]*(A[4]*A[8]-A[5]*A[7]) - A[1]*(b[1]*A[8]-A[5]*b[2]) + A[2]*(b[1]*A[7]-A[4]*b[2]);
      detY = A[0]*(b[1]*A[8]-A[5]*b[2]) - b[0]*(A[3]*A[8]-A[5]*A[6]) + A[2]*(A[3]*b[2]-b[1]*A[6]);
      detZ = A[0]*(A[4]*b[2]-b[1]*A[7]) - A[1]*(A[3]*b[2]-b[1]*A[6]) + b[0]*(A[3]*A[7]-A[4]*A[6]);
      b[0] = detX/detA;
      b[1] = detY/detA;
      b[2] = detZ/detA;
    }
  }

//The function compute the determinant of a NxN matrix according to Cramer method
  double det(int N, double A[])
  {
    int dim = N*N;
    // int Nm1 = N-1;
    double C[(N-1)*(N-1)];
    double sum = 0.0;

    if (N == 2) {
      return A[0]*A[3] - A[1]*A[2];
    }
    else {
      for (int i=0; i < N; i++) {
        int j = 0;
        for (int z = N; z < dim; z++) {
          if ((dim-z+i) % N != 0) {
            C[j] = A[z];
            j++;
          }
        }
          int r = i/N;
          int c = i%N;
          sum += ((r+c)%2==0 ? +1:-1)*A[i]*det(N-1, C);
      }
      return sum;
    }
  }

  void Laplace(int N, double A[], double b[])
  {
    int dim = N*N;
    double detA = det(N, A);
    double M[dim];
    double detX = 0.0;
    double x[N];

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < dim; j++) {
        if (j%N == i) {
          M[j] = b[j/N];
        }
        else {
          M[j] = A[j];
        }
      }
      detX = det(N, M);
      x[i] = detX/detA;
    }
    for (int i = 0; i < N; i++) {
      b[i] = x[i];
    }
  }

}
