
# CONSOLA !pip install folium

import folium
from folium import LayerControl
# Crear un mapa centrado en Lima
mapaBurrito = folium.Map(location=[-12.046374, -77.042793], zoom_start=12)

# Coordenadas aproximadas de cada paradero
paraderosIda = {
    "Av. Universitaria y Av. Jamaica ": [-11.925820, -77.051705],
    "Av. Universitaria y Av. Micaela Bastidas": [-11.929785, -77.053481],
    "Av. Universitaria y Av. El Retablo": [-11.926598, -77.055046],
    "Av. Universitaria y Av. 22 de agosto": [-11.945937, -77.060870],
    "Av. Universitaria y Av. México": [-11.955330, -77.059684],
    "Av. Universitaria y Ovalo Comas": [-11.962410, -77.062022],
    "Universitaria y Av. Villa Sol": [-11.962488, -77.062060],
    "Universitaria y Av. Los Alisos": [-11.983355, -77.078546],
    "Av. Izaguirre y Av. 12 de octubre": [-11.990652, -77.092866],
    "Av. Las Vaquitas": [-12.001233, -77.091344],
    "San Marcos": [-12.061365, -77.086012]
}

# Coordenadas aproximadas de cada paradero para el recorrido de vuelta
paraderosVuelta = {
    "San Marcos": [-12.061365, -77.086012],
    "Av. Benavides": [-12.049904, -77.077915],
    "Av. Argentina": [-12.047277, -77.084353],
    "Av. Perú": [-12.031596, -77.079706],
    "Av. José Granda": [-12.026041, -77.074942],
    "Av. San German": [ -12.019030, -77.079754],
    "Av. Tomas Valle": [ -12.012889, -77.080080],
    "Av. Angélica Gamarra": [ -12.006466, -77.076082],
    "Av. Mayolo": [-11.996083, -77.083391],
    "Av. Izaguirre": [-11.990979, -77.070450],
    "Av. Alisos": [-11.981917, -77.093349],
    "Av. Naranjal": [-11.978700, -77.073476],
    "Av. Marañón": [-11.971721, -77.076285],
    "Av. Villa Sol": [-11.964144, -77.071830],
    " Panamericana Norte": [-11.952899, -77.069925],
    " Av. Metropolitana": [-11.952938, -77.064593],
    " Av. México": [-11.955414, -77.059716],
    " Av. 22 de agosto": [-11.948739, -77.058071],
    " Av. Belaunde": [-11.934615, -77.056875],
    "Av. Micaela Bastidas": [-11.929081, -77.055446],
    "Av. Jamaica": [-11.927412, -77.048973],
    "Av. Los Incas": [-11.914493, -77.049078],
    "Hospital Sergio Bernales de Collique en Comas": [-11.913653, -77.039559]
}

# Crear capas para la ruta de ida y la ruta de vuelta
rutaIda = folium.FeatureGroup(name="Ruta de Ida")
rutaVuelta = folium.FeatureGroup(name="Ruta de Vuelta")

# Añadir los marcadores de los paraderos del recorrido de ida
for paradero, coordenadas in paraderosIda.items():
    folium.Marker(location=coordenadas, popup=paradero).add_to(rutaIda)

# Añadir los marcadores de los paraderos del recorrido de vuelta
for paradero, coordenadas in paraderosVuelta.items():
    folium.Marker(location=coordenadas, popup=paradero).add_to(rutaVuelta)

# Dibujar la ruta de ida (línea) entre los paraderos
coordenadasRutaIda = list(paraderosIda.values())
folium.PolyLine(locations=coordenadasRutaIda, color="blue", weight=5, opacity=0.7).add_to(rutaIda)

# Dibujar la ruta de vuelta (línea) entre los paraderos
coordenadasRutaVuelta = list(paraderosVuelta.values())
folium.PolyLine(locations=coordenadasRutaVuelta, color="red", weight=5, opacity=0.7).add_to(rutaVuelta)

# Añadir las capas al mapa
rutaIda.add_to(mapaBurrito)
rutaVuelta.add_to(mapaBurrito)

# Añadir control de capas para alternar entre rutas
LayerControl().add_to(mapaBurrito)

# Guardar el mapa en un archivo HTML
mapaBurrito.save("rutaBurritoConoNorte.html")