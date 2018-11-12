#
#  rbpLocator.s
#  MinecraftBlacksmith
#
#  Created by Hallowizer on 11/11/18.
#
#

.section __TEXT,__text     # Code section
                           #
getRbp:                    # Function getRbp
    movq %rbp, %eax        # Put the rbp value into eax, the return register.
    retq                   # Return.
