#!/home/noah/.asdf/shims/octave -qf

ncol = 99;
[dat, pos, err] = textscan(stdin, "%c", "Whitespace", "\n");
M = cell2mat(cell2mat(dat(1,1))) - '0';
M = reshape(M, rows(M)/ncol, ncol).';

I = zeros(size(M));
for f = 1:2,
  for i = 1:2,
    A = cummax(M);
    X = M > [zeros(1,columns(A))-1; A(1:rows(A)-1,:)];
    I |= X;
    I = flipud(I);
    M = flipud(M);
  end;
  M = M.';
  I = I.';
end;

res = sum(sum(I));
fprintf(stdout, "Part 2: %d\n", res);
