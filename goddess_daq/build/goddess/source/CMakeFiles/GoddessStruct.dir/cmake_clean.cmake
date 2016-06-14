FILE(REMOVE_RECURSE
  "libGoddessStruct.pdb"
  "libGoddessStruct.so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/GoddessStruct.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
