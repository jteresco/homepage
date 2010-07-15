#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include "MSops.h"
#include "pmshops.h"

main(
int argc,
char *argv[])
{
   pMesh      mesh          ;      /*  MDB mesh handle                  */
   pGModel    model         ;      /*  MDB model handle                 */
   pMeshPB    pmeshpb       ;      /*  PMDB distributed mesh handle     */
   char       file[20]      ;      /*  string                           */
   int        rc            ;      /*  return code                      */
   int        axes[]= {0,1} ;      /*  axis used for orthogonal 
                                       bisection                        */
   int        num_axes = 2  ;      /*  number of axes                   */
   

   rc=MPI_Init(&argc, &argv);      /* initialize MPI                    */

   MD_init() ;                     /* MDB: initialize the mesh database */
   model = GM_new(0) ;             /* MDB: initialize geometric model   */

   sprintf(file,"%s.smd",argv[1]) ;

   M_load(model,file) ;            /* MDB: load geometric model         */
   pmdb_ge_tabl_new(model) ;       /* initialize geometric entity hash
                                      table on all processors           */

   mesh = MM_new(1,model) ;        /* MDB: initialize a mesh object     */
   
   pmdb_ortho_rb(argv[1],num_axes,axes,mesh,&pmeshpb) ; /* load mesh and 
                                      inertial partitioning             */

   do_something(argv[1],mesh,pmeshpb) ; 

   M_delete(mesh) ; 
   MD_exit() ; 

   MPI_Finalize() ;                /* finalize MPI                      */
}
