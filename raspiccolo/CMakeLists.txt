set(ROOT_FOLDER_NAME "raspiccolo")

# Not really needed as its nicly abstracted by the pico sdk but could be useful to make it even more abstracted... but for now lets ignore it.
#add_subdirectory(i2c)

add_subdirectory(i2c)
add_subdirectory(memory)
add_subdirectory(pwm)

