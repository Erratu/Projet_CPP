cmake_minimum_required(VERSION 3.16)
project(Doc)

# Cherche Doxygen
find_package(Doxygen REQUIRED)

# Fichier Doxyfile source
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/doxyfilerc)
# Fichier Doxyfile de sortie (généré pour le build)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/doxyfilerc)

# Remplacer les variables @...@ et générer le fichier de sortie
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

# Ajouter une cible make doc
add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Génération de la documentation Doxygen"
    VERBATIM
)
