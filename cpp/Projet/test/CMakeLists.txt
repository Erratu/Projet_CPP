# Créer un executable à partir de fichiers sources
add_executable(test_vec  test_vec.cpp)
add_executable(test_univ  test_univ.cpp)

# Fait le lien avec la bibliothèque créée précedemment
# Les entêtes sont automatiquement détectés.
target_link_libraries(test_vec particules)
target_link_libraries(test_univ particules)