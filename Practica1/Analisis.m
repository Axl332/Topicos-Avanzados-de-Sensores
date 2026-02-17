%Analisis
%Integrantes:
% - Axel Perea Pinedo
% - Diego Guillermo Guardado Viramontes
% - Valeria Carrillo Hernández
clc;
clear;


archivos = {'Calles.mat', 'Campo_Abierto.mat', 'Lugar_cerrado.mat'};
nombres = {'Calles', 'Campo Abierto', 'Lugar Cerrado'};

for i = 1:length(archivos)
    data = load(archivos{i});
    lat = data.Position.latitude;
    lon = data.Position.longitude;
    alt = data.Position.altitude;
    
    % --- 1. PROMEDIOS  ---
    prom_lat = mean(lat);
    prom_lon = mean(lon);
    prom_alt = mean(alt);
    
    % --- 2. CONVERSIÓN A METROS PARA ANÁLISIS DE ERROR ---
    % 1 grado latitud aprox 111,320m. 1 grado longitud aprox 111,320 * cos(lat)
    lat_m = (lat - prom_lat) * 111320;
    lon_m = (lon - prom_lon) * (111320 * cosd(prom_lat));
    alt_m = alt - prom_alt; % La altitud ya está en metros
    
    % --- 3. DESVIACIÓN ESTÁNDAR (Precisión en metros) ---
    std_lat = std(lat_m);
    std_lon = std(lon_m);
    std_alt = std(alt_m);
    
    % --- 4. ERROR MEDIO CUADRÁTICO (RMSE) ---
    rmse_lat = sqrt(mean(lat_m.^2));
    rmse_lon = sqrt(mean(lon_m.^2));
    rmse_alt = sqrt(mean(alt_m.^2));
    
    % --- 5. NORMALIZACIÓN  ---
    norm_lat = (lat - min(lat)) / (max(lat) - min(lat));
    norm_lon = (lon - min(lon)) / (max(lon) - min(lon));
    
    % Mostrar Resultados en Consola
    fprintf('\n=== ANÁLISIS ESTADÍSTICO: %s ===\n', nombres{i});
    fprintf('Promedio -> Lat: %.6f, Lon: %.6f, Alt: %.2f m\n', prom_lat, prom_lon, prom_alt);
    fprintf('Desv. Estándar (Metros) -> Lat: %.2fm, Lon: %.2fm, Alt: %.2fm\n', std_lat, std_lon, std_alt);
    fprintf('RMSE (Error) -> Lat: %.2fm, Lon: %.2fm, Alt: %.2fm\n', rmse_lat, rmse_lon, rmse_alt);
    fprintf('--------------------------------------------------\n');
end