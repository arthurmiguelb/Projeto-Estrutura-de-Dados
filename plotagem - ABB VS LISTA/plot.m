comp1 = csvread('lista.csv');
x1 = comp1(:,1);
y1 = comp1(:,2);

comp2 = csvread('abb.csv');
x2 = comp2(:,1);
y2 = comp2(:,2);
figure(1);

subplot(1,2,1);
plot(x1, y1, 'k');
axis([0,2000,0,2000]);
title('Lista Encadeada');

subplot(1,2,2);
plot(x2, y2, 'b');
axis([0,2000,0,2000]);
title('Árvore de Busca Binária');