# Course: High Performance Computing 2021/2022
# 
# Lecturer: Francesco Moscato	fmoscato@unisa.it
#
# Group:
# Salvatore Grimaldi        0622701742      s.grimaldi29@studenti.unisa.it              
# Enrico Maria Di Mauro     0622701706      e.dimauro5@studenti.unisa.it
# Allegra Cuzzocrea         0622701707      a.cuzzocrea2@studenti.unisa.it
# 
# 
# Copyright (C) 2021 - All Rights Reserved 
#
# This file is part of Contest-MPI.
#
# Contest-MPI is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Contest-MPI is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Contest-MPI.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.9)

project(CMakeTestProject2)

add_executable(eseguibileO0 src/main.c src/countingsort.c include/countingsort.h)
add_executable(eseguibileO1 src/main.c src/countingsort.c include/countingsort.h)
add_executable(eseguibileO2 src/main.c src/countingsort.c include/countingsort.h)
add_executable(eseguibileO3 src/main.c src/countingsort.c include/countingsort.h)
add_executable(eseguibileSeqO0 src/mainS.c)
add_executable(eseguibileSeqO1 src/mainS.c)
add_executable(eseguibileSeqO2 src/mainS.c)
add_executable(eseguibileSeqO3 src/mainS.c)

target_include_directories(eseguibileO0 PRIVATE include)
target_include_directories(eseguibileO1 PRIVATE include)
target_include_directories(eseguibileO2 PRIVATE include)
target_include_directories(eseguibileO3 PRIVATE include)
target_include_directories(eseguibileSeqO0 PRIVATE include)
target_include_directories(eseguibileSeqO1 PRIVATE include)
target_include_directories(eseguibileSeqO2 PRIVATE include)
target_include_directories(eseguibileSeqO3 PRIVATE include)


find_package(MPI REQUIRED)
if(MPI_C_FOUND)
        target_link_libraries(eseguibileO0 PUBLIC MPI::MPI_C) #linko la libreria MPI
        target_link_libraries(eseguibileO1 PUBLIC MPI::MPI_C) #linko la libreria MPI
        target_link_libraries(eseguibileO2 PUBLIC MPI::MPI_C) #linko la libreria MPI
        target_link_libraries(eseguibileO3 PUBLIC MPI::MPI_C) #linko la libreria MPI
        message("MPI Trovato")
else()
    message("Non è stata trovato MPI")
endif()

target_compile_options(eseguibileO0 PRIVATE -O0) #ottimizzazioni 0
target_compile_options(eseguibileO1 PRIVATE -O1) #ottimizzazioni 1
target_compile_options(eseguibileO2 PRIVATE -O2) #ottimizzazioni 2
target_compile_options(eseguibileO3 PRIVATE -O3) #ottimizzazioni 3
target_compile_options(eseguibileSeqO0 PRIVATE -O0) #ottimizzazioni sequenziale 0
target_compile_options(eseguibileSeqO1 PRIVATE -O1) #ottimizzazioni sequenziale 1
target_compile_options(eseguibileSeqO2 PRIVATE -O2) #ottimizzazioni sequenziale 2
target_compile_options(eseguibileSeqO3 PRIVATE -O3) #ottimizzazioni sequenziale 3

add_custom_target(
    generate_output
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/measure/file.bash ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Inizio Misure"
    DEPENDS	
		eseguibileO0
        eseguibileO1
        eseguibileO2
        eseguibileO3
        eseguibileSeqO0
        eseguibileSeqO1
        eseguibileSeqO2
        eseguibileSeqO3
)

# --------------------------------- MEASURES EXTRACTION ---------------------------------
find_package(Python3 COMPONENTS Interpreter REQUIRED)
find_program(PipEnv pipenv REQUIRED)

add_custom_target(
	 install_pipenv
	 COMMAND PIPENV_PIPFILE=${CMAKE_CURRENT_SOURCE_DIR}/Pipfile ${PipEnv} install --ignore-pipfile
    COMMENT "Installing pipenv dependencies [${PipEnv} install]"
    DEPENDS	${CMAKE_CURRENT_SOURCE_DIR}/Pipfile.lock
)

add_custom_target(
    extract_measures
    COMMAND PIPENV_PIPFILE=${CMAKE_CURRENT_SOURCE_DIR}/Pipfile ${PipEnv} run python ${CMAKE_CURRENT_SOURCE_DIR}/measure/extract.py
    COMMENT "Generating version header [${PipEnv} run python ${CMAKE_CURRENT_SOURCE_DIR}/measure/extract.py]"
    DEPENDS	
		install_pipenv
		${CMAKE_CURRENT_SOURCE_DIR}/measure/extract.py
)