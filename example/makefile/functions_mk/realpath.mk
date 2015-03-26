#$(realpath names¡­)
#For each file name in @names return the canonical absolute name. A canonical name d-
#oes not contain any . or .. components, nor any repeated path separators (/) or sym-
#links. In case of a failure the empty string is returned. Consult the realpath(3) d-
#ocumentation for a list of possible failure causes.