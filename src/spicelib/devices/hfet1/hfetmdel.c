/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 S. Hwang
**********/

/*
  Imported into hfeta model: Paolo Nenzi 2001
*/

#include "ngspice/ngspice.h"
#include "hfetdefs.h"
#include "ngspice/sperror.h"
#include "ngspice/suffix.h"


int
HFETAmDelete(GENmodel **models, IFuid modname, GENmodel *kill)
{
    GENinstance *here;
    GENmodel **prev = models;
    GENmodel *model = *prev;

    for (; model; model = model->GENnextModel) {
        if (model->GENmodName == modname || (kill && model == kill))
            goto delgot;
        prev = &(model->GENnextModel);
    }

    return E_NOMOD;

 delgot:
    *prev = model->GENnextModel;
    for (here = model->GENinstances; here;) {
        GENinstance *next_instance = here->GENnextInstance;
        FREE(here);
        here = next_instance;
    }
    FREE(model);
    return OK;
}
