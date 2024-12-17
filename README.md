# **Super-SNID Templates**

SNID (Supernova Identification) is a widely used code which is capable of determining the type, redshift and age from explosion of an observed spectrum by cross-matching with a library of templates. Currently SNID contains few to no examples of rarer transient types discovered since the code's creation. Super-SNID is an expanded library of templates for SNID which improves its capability to age and identify these rarer transient subtypes. This was developed for a Summer Studentship project at the Astrophysics Research Centre at Queen's University Belfast. A 'Template Generator' code is also available which can be used to append new spectra to the library.

## **Super-SNID Templates Installation Instructions**

**Replace Files in Source Folder**

Download the ‘snid.inc’ and ‘typeinfo.f’ files from the GitHub.

‘snid.inc’ defines the number of types and subtypes allowed in SNID. ‘typeinfo.f’ defines the types and subtypes.

Replace the existing files in the ‘Source’ folder in SNID with these new files.

**Import New Templates**

Download the compressed ‘Super-SNID Templates’ folder from the GitHub.

Expand the folder and copy the new templates into the ‘templates’ folder in SNID. 

Download the ‘templist’ file from the GitHub and replace the existing ‘templist’ file in the ‘templates’ folder with this new file.

**Recompile SNID**

Finally, it is necessary to recompile SNID in order to enact these changes.

To do so run the following two commands in the terminal while in the SNID folder :

make realclean; make

make install

**Your SNID should now contain the additional Super-SNID templates and subtypes.**

