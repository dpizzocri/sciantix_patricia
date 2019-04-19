% This script is the driver for the generation of nuclear data
% It automatically prepares Serpent inputs at various enrichment 
% and provides the considered cross sections (fission and absorption)
% as a function of enrichment and burnup in a C++-like shape.
% It produces also the 016 (n,alpha) cross sections as a function of 
% enrichments and burnup.
%NB: The considered Serpent input models a single pin of a standard PWR

%NBB: the provided Serpent input should be modified according to 
% cross section and decays libraries location and Serpent executable location

% NBBB: the input has been checked and built for the version 2_1_28 of Serpent

clc
close all
clear all

names = cell(1,21);
names{1} = 'U235';
names{2} = 'U236';
names{3} = 'U238';
names{4} = 'Np237';
names{5} = 'Np238';
names{6} = 'Np239';
names{7} = 'Pu238';
names{8} = 'Pu239';
names{9} = 'Pu240';
names{10} = 'Pu241';
names{11} = 'Pu242';
names{12} = 'Pu243';
names{13} = 'Am241';
names{14} = 'Am242g';
names{15} = 'Am242m';
names{16} = 'Am243';
names{17} = 'Am244';
names{18} = 'Cm242';
names{19} = 'Cm243';
names{20} = 'Cm244';
names{21} = 'Cm245';

enrichment = [1:5];
burnup_steps = 31;

xsections_c=zeros(length(names), length(enrichment), burnup_steps);
xsections_f=zeros(length(names), length(enrichment), burnup_steps);
xsections_na=zeros(length(enrichment), burnup_steps);

for i=1:length(enrichment)
     
    [a,b,c] = runSerpent(enrichment(i));
    
    for k=1:length(names)
        
        for j=1:burnup_steps
            
            xsections_f(k, i, j) = a(k, j);
            xsections_c(k, i, j) = b(k, j);
            xsections_na(i,j) = c(j);
            
        end
        
    end
    
end


fid = fopen('xsec_f.txt', 'w');

fprintf(fid, 'const double xsec_fiss_table[%d][%d][%d]=\r\n{\r\n', length(names), length(enrichment), burnup_steps);

for ii=1:length(names)
    
    fprintf(fid, ['/*', char(names(ii)), '*/{\r\n']);
    for jj=1:length(enrichment)
        fprintf(fid, '/*%.1f %c*/ {', enrichment(jj), '%');
        for kk=1:burnup_steps
            fprintf(fid, '%.2f, ', xsections_f(ii, jj, kk));
        end
        fprintf(fid, '},\r\n');
    end
    fprintf(fid, '},\r\n');
end

fid2 = fopen('xsec_c.txt', 'w');

fprintf(fid2, 'const double xsec_capt_table[%d][%d][%d]=\r\n{\r\n', length(names), length(enrichment), burnup_steps);

for ii=1:length(names)
    
    fprintf(fid2, ['/*', char(names(ii)), '*/{\r\n']);
    for jj=1:length(enrichment)
        fprintf(fid2, '/*%.1f %c*/ {', enrichment(jj), '%');
        for kk=1:burnup_steps
            fprintf(fid2, '%.2f, ', xsections_c(ii, jj, kk));
        end
        fprintf(fid2, '},\r\n');
    end
    fprintf(fid2, '},\r\n');
end

fid3 = fopen('xsec_na.txt', 'w');
fprintf(fid3, 'const double xsec_na_table[%d][%d]=\r\n{\r\n', length(enrichment), burnup_steps);
fprintf(fid3, ['/*', 'O16', '*/{\r\n']);
    for jj=1:length(enrichment)
        fprintf(fid3, '/*%.1f %c*/ {', enrichment(jj), '%');
        for kk=1:burnup_steps
            fprintf(fid3, '%.2e, ', xsections_na(jj, kk));
        end
        fprintf(fid3, '},\r\n');
    end
fprintf(fid3, '},\r\n');
