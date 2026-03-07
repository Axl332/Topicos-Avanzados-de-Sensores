% 1. Definir los datos de la tabla
tiempo = [50, 100, 150, 200, 250, 300, 350, 400, 450];
distancia = [145, 154, 174, 165, 96, 34, 41, 84, 166];

% 2. Crear la figura y graficar
figure;
plot(tiempo, distancia, '-o', 'LineWidth', 2, 'MarkerSize', 8, 'MarkerFaceColor', 'r');

% 3. Personalizar la gráfica
title('Relación Tiempo vs Distancia');
xlabel('Tiempo (ms)');
ylabel('Distancia');
grid on;