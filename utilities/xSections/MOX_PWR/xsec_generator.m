%% Stefano Altieri, MSc Thesis, Polimi, 2019 %%

clc
close all
clear all %#ok<CLSCR>

names = cell(1,23);
names{1} = 'U234';
names{2} = 'U235';
names{3} = 'U236';
names{4} = 'U237';
names{5} = 'U238';
names{6} = 'Np237';
names{7} = 'Np238';
names{8} = 'Np239';
names{9} = 'Pu238';
names{10} = 'Pu239';
names{11} = 'Pu240';
names{12} = 'Pu241';
names{13} = 'Pu242';
names{14} = 'Pu243';
names{15} = 'Am241';
names{16} = 'Am242g';
names{17} = 'Am242m';
names{18} = 'Am243';
names{19} = 'Am244';
names{20} = 'Cm242';
names{21} = 'Cm243';
names{22} = 'Cm244';
names{23} = 'Cm245';

enrichment = 5:10;
burnup_steps = 31;

xsections_c=zeros(length(names), length(enrichment), burnup_steps);
xsections_f=zeros(length(names), length(enrichment), burnup_steps);
xsections_na=zeros(length(enrichment), burnup_steps);
xsections_n2n=zeros(length(enrichment), burnup_steps);
xsections_n3n=zeros(length(enrichment), burnup_steps);

for i=1:length(enrichment)
     
    [a,b,c,d,e] = runSerpent(enrichment(i));
    
    for k=1:length(names)
        
        for j=1:burnup_steps
            
            xsections_f(k, i, j) = a(k, j);
            xsections_c(k, i, j) = b(k, j);
            xsections_na(i,j) = c(j);
            xsections_n2n(i,j) = d(j);
            xsections_n3n(i,j) = e(j);
            
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
            fprintf(fid, '%.4f, ', xsections_f(ii, jj, kk));
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
            fprintf(fid2, '%.4f, ', xsections_c(ii, jj, kk));
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
            fprintf(fid3, '%.4f, ', xsections_na(jj, kk));
        end
        fprintf(fid3, '},\r\n');
    end
fprintf(fid3, '},\r\n');

%%
fid4 = fopen('xsec_n2n.txt', 'w');
fprintf(fid4, 'const double xsec_n2n_table[%d][%d]=\r\n{\r\n', length(enrichment), burnup_steps);
fprintf(fid4, ['/*', 'U238', '*/{\r\n']);
    for jj=1:length(enrichment)
        fprintf(fid4, '/*%.1f %c*/ {', enrichment(jj), '%');
        for kk=1:burnup_steps
            fprintf(fid4, '%.4f, ', xsections_n2n(jj, kk));
        end
        fprintf(fid4, '},\r\n');
    end
fprintf(fid4, '},\r\n');

%%
fid5 = fopen('xsec_n3n.txt', 'w');
fprintf(fid5, 'const double xsec_n3n_table[%d][%d]=\r\n{\r\n', length(enrichment), burnup_steps);
fprintf(fid5, ['/*', 'U238', '*/{\r\n']);
    for jj=1:length(enrichment)
        fprintf(fid5, '/*%.1f %c*/ {', enrichment(jj), '%');
        for kk=1:burnup_steps
            fprintf(fid5, '%.6f, ', xsections_n3n(jj, kk));
        end
        fprintf(fid5, '},\r\n');
    end
fprintf(fid5, '},\r\n');
