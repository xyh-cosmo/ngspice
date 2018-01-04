/**********
Copyright 1992 Regents of the University of California.  All rights reserved.
Author: 1987 Kartikeya Mayaram, U. C. Berkeley CAD Group
**********/

/*
 * This routine deletes a NBJT model from the circuit and frees the storage
 * it was using. returns an error if the model has instances
 */

#include "ngspice/ngspice.h"
#include "nbjtdefs.h"
#include "ngspice/sperror.h"
#include "ngspice/suffix.h"


int
NBJTmDelete(GENmodel **models, IFuid modname, GENmodel *kill)
{
    GENmodel **prev = models;
    GENmodel *model = *prev;

    for (; model; model = model->GENnextModel) {
        if (model->GENmodName == modname || (kill && model == kill))
            goto delgot;
        prev = &(model->GENnextModel);
    }

    return E_NOMOD;

 delgot:
    if (model->GENinstances)
        return E_NOTEMPTY;
    *prev = model->GENnextModel;
    FREE(model);
    return OK;
}
