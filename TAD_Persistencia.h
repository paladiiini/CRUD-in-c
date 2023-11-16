/* --------------------------
   Tipos de dados
   -------------------------- */
typedef struct dFile DFile;
typedef DFile*       pDFile;

typedef int   (*FuncaoComparacao)(void *, void *);
typedef void* (*FuncaoAloca)     ();
typedef void  (*FuncaoImpressao) (void *);
typedef int   (*FuncaoPredicado) (void *);

/* --------------------------
   Operações CRUD
   -------------------------- */
pDFile  open      (char[30], int);
void    createe   (pDFile, void*);                          // dados
void*   retrieve  (pDFile, void*, FuncaoComparacao);        // chave
void    update    (pDFile, void*, void*, FuncaoComparacao, FuncaoAloca); // chave e os dados
void    delete    (pDFile, void*, FuncaoComparacao);        // chave
void    close     (pDFile);

pDLista queryAll  (pDFile, FuncaoAloca);
pDLista queryBy   (pDFile, FuncaoPredicado);
void   persistAll (pDFile, pDLista);




