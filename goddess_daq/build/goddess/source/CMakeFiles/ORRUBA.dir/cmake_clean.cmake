FILE(REMOVE_RECURSE
  "libORRUBA.pdb"
  "libORRUBA.so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ORRUBA.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
