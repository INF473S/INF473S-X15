INCLUDE ( SBVersion )

ADD_DEFINITIONS(-DSB_SDK_MAJOR_VERSION_NUMBER=${majorVersion})
ADD_DEFINITIONS(-DSB_SDK_MINOR_VERSION_NUMBER=${minorVersion})
ADD_DEFINITIONS(-DSB_SDK_PATCH_VERSION_NUMBER=${patchVersion})
ADD_DEFINITIONS(-DSB_SDK_VERSION_NUMBER_STRING=${versionString})
ADD_DEFINITIONS(-DSB_SDK_VERSION_NUMBER=SBVersionNumber\(${majorVersion},\ ${minorVersion},\ ${patchVersion}\))
