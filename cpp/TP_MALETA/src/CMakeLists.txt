# Créer une bibliothèque à partir d'un ensemble de fichiers de définitions (.cxx) sans main.
# Ces fichiers ne contiennent pas de fonction main
# Remplacer ... par les fichiers nécessaires 
add_library(particules 
    univers.cpp
)

target_include_directories(particules PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)