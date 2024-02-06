DESCRIPTION = "Custom Image"

LICENSE = "CLOSED"

# core files basic console boot.
IMAGE_INSTALL = "packagegroup-core-boot"

#desired packages for splash and ssh
IMAGE_INSTALL += "psplash dropbear"

inherit core-image

require recipes-core/packagegroups/packagegroup-custom.bb

IMAGE_INSTALL += "${CUSTOM_IMAGE_FEATURES}"
