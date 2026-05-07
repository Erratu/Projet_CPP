include(GoogleTest)
set(TEST_FILES "test_vecteur" "test_univers" "test_particule" "test_limites")

# Créer un executable à partir de fichiers sources
foreach(T ${TEST_FILES})
    # Crée l'exécutable pour la famille de test
    add_executable(${T} "${CMAKE_CURRENT_SOURCE_DIR}/${T}.cpp")
    
    # Lie avec GTest
    target_link_libraries(${T} GTest::gtest_main)
    
    # Permet à CMake de découvrir les tests individuels
    gtest_discover_tests(${T})
endforeach()