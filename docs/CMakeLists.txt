find_package(Doxygen REQUIRED)
find_package(Sphinx REQUIRED)

set(DOXYFILE_ROOT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/doxygen")
set(SPHINX_ROOT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/sphinx")

set(SPHINX_CSS "css/style.css" "css/colours.css" "css/defaults.css"
               "css/dark.css" "css/light.css")

# set(SPHINX_JS "js/main.js")

# set(SPHINX_ICON_IMAGE_PATH "\"img/<ICON_IMAGE>.svg\"")

set(SPHINX_RESTRUCTRED_TEXT
    # Root Index
    "${SPHINX_ROOT_DIRECTORY}/index.rst"
    "${SPHINX_ROOT_DIRECTORY}/raspiccolo/pwm/index.rst")

add_doxygen_docs(
  Doxygen_raspiccolo
  DOXYFILE_IN
  "${DOXYFILE_ROOT_DIRECTORY}/Doxyfile.in"
  DOXYFILE_OUT
  "${DOXYFILE_ROOT_DIRECTORY}/Doxyfile"
  GENERATE_XML
  GENERATE_MAN
  JAVADOC_BANNER
  TARGETS
  raspiccolo_pwm)

add_sphinx_docs(
  Sphinx_raspiccolo
  CONF_IN
  "${SPHINX_ROOT_DIRECTORY}/conf.py.in"
  CONF_OUT
  "${SPHINX_ROOT_DIRECTORY}/conf.py"
  RESTRUCTRED_TEXT
  ${SPHINX_RESTRUCTRED_TEXT}
  CSS
  ${SPHINX_CSS}
  BREATHE_DOMAIN_ALL_CPP)

add_dependencies(Sphinx_raspiccolo Doxygen_raspiccolo)

set_target_properties(Doxygen_raspiccolo Sphinx_raspiccolo PROPERTIES FOLDER Docs
                                                            EXCLUDE_FROM_ALL ON)
