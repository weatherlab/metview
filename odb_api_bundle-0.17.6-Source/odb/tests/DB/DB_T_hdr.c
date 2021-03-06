#undef ODB_MAINCODE
#undef IS_a_VIEW
#define IS_a_TABLE_hdr 1
#include "DB.h"

extern double USD_mdi_DB; /* $mdi */


PUBLIC int
DB_Pack_T_hdr(void *T)
{
  int Nbytes = 0;
  TABLE_hdr *P = T;
  Packed_DS *PDS;
  if (P->Is_loaded) {
    PDS = PackDS(P, DB, pk1int, seqno); CHECK_PDS_ERROR(1);
    PDS = PackDS(P, DB, yyyymmdd, date); CHECK_PDS_ERROR(2);
    PDS = PackDS(P, DB, hhmmss, time); CHECK_PDS_ERROR(3);
    PDS = PackDS(P, DB, string, statid); CHECK_PDS_ERROR(4);
    PDS = PackDS(P, DB, pk9real, lat); CHECK_PDS_ERROR(5);
    PDS = PackDS(P, DB, pk9real, lon); CHECK_PDS_ERROR(6);
    PDS = PackDS(P, DB, linkoffset_t, LINKOFFSET(body)); CHECK_PDS_ERROR(7);
    PDS = PackDS(P, DB, linklen_t, LINKLEN(body)); CHECK_PDS_ERROR(8);
  }
  return Nbytes;
}

PUBLIC int
DB_Unpack_T_hdr(void *T)
{
  int Nbytes = 0;
  TABLE_hdr *P = T;
  if (P->Is_loaded) {
    UseDS(P, DB, pk1int, seqno); Nbytes += BYTESIZE(P->seqno.d);
    UseDS(P, DB, yyyymmdd, date); Nbytes += BYTESIZE(P->date.d);
    UseDS(P, DB, hhmmss, time); Nbytes += BYTESIZE(P->time.d);
    UseDS(P, DB, string, statid); Nbytes += BYTESIZE(P->statid.d);
    UseDS(P, DB, pk9real, lat); Nbytes += BYTESIZE(P->lat.d);
    UseDS(P, DB, pk9real, lon); Nbytes += BYTESIZE(P->lon.d);
    UseDS(P, DB, linkoffset_t, LINKOFFSET(body)); Nbytes += BYTESIZE(P->LINKOFFSET(body).d);
    UseDS(P, DB, linklen_t, LINKLEN(body)); Nbytes += BYTESIZE(P->LINKLEN(body).d);
  }
  return Nbytes;
}

PUBLIC int
DB_Sel_T_hdr(void *T, ODB_PE_Info *PEinfo, int phase, void *feedback)
{
  TABLE_hdr *P = T;
  ODBMAC_TABLE_DELAYED_LOAD(hdr);
  return P->Nrows;
}


PreGetTable(DB, d, double, hdr)
  Call_CopyGet_TABLE(DB, d, 1, hdr, pk1int, D, seqno, Count, DATATYPE_INT4);
  Call_CopyGet_TABLE(DB, d, 2, hdr, yyyymmdd, D, date, Count, DATATYPE_YYYYMMDD);
  Call_CopyGet_TABLE(DB, d, 3, hdr, hhmmss, D, time, Count, DATATYPE_HHMMSS);
  Call_CopyGet_TABLE(DB, d, 4, hdr, string, D, statid, Count, DATATYPE_STRING);
  Call_CopyGet_TABLE(DB, d, 5, hdr, pk9real, D, lat, Count, DATATYPE_REAL8);
  Call_CopyGet_TABLE(DB, d, 6, hdr, pk9real, D, lon, Count, DATATYPE_REAL8);
  Call_CopyGet_TABLE(DB, d, 7, hdr, linkoffset_t, D, LINKOFFSET(body), Count, DATATYPE_LINKOFFSET);
  Call_CopyGet_TABLE(DB, d, 8, hdr, linklen_t, D, LINKLEN(body), Count, DATATYPE_LINKLEN);
PostGetTable(d, double, hdr)


PrePutTable(DB, d, double, hdr)
  Call_CopyPut_TABLE(DB, d, 1, hdr, pk1int, seqno, D, Count, DATATYPE_INT4);
  Call_CopyPut_TABLE(DB, d, 2, hdr, yyyymmdd, date, D, Count, DATATYPE_YYYYMMDD);
  Call_CopyPut_TABLE(DB, d, 3, hdr, hhmmss, time, D, Count, DATATYPE_HHMMSS);
  Call_CopyPut_TABLE(DB, d, 4, hdr, string, statid, D, Count, DATATYPE_STRING);
  Call_CopyPut_TABLE(DB, d, 5, hdr, pk9real, lat, D, Count, DATATYPE_REAL8);
  Call_CopyPut_TABLE(DB, d, 6, hdr, pk9real, lon, D, Count, DATATYPE_REAL8);
  Call_CopyPut_TABLE(DB, d, 7, hdr, linkoffset_t, LINKOFFSET(body), D, Count, DATATYPE_LINKOFFSET);
  Call_CopyPut_TABLE(DB, d, 8, hdr, linklen_t, LINKLEN(body), D, Count, DATATYPE_LINKLEN);
PostPutTable(d, double, hdr)

PreLoadTable(DB, hdr);
  Call_Read_DS(DB, fp_idx, filename, Nbytes, pk1int, DATATYPE_INT4, seqno);
  Call_Read_DS(DB, fp_idx, filename, Nbytes, yyyymmdd, DATATYPE_YYYYMMDD, date);
  Call_Read_DS(DB, fp_idx, filename, Nbytes, hhmmss, DATATYPE_HHMMSS, time);
  Call_Read_DS(DB, fp_idx, filename, Nbytes, string, DATATYPE_STRING, statid);
  Call_Read_DS(DB, fp_idx, filename, Nbytes, pk9real, DATATYPE_REAL8, lat);
  Call_Read_DS(DB, fp_idx, filename, Nbytes, pk9real, DATATYPE_REAL8, lon);
  Call_Read_DS(DB, fp_idx, filename, Nbytes, linkoffset_t, DATATYPE_LINKOFFSET, LINKOFFSET(body));
  Call_Read_DS(DB, fp_idx, filename, Nbytes, linklen_t, DATATYPE_LINKLEN, LINKLEN(body));
PostLoadTable(hdr)

PreStoreTable(DB, hdr);
  Call_Write_DS(DB, fp_idx, filename, Nbytes, pk1int, DATATYPE_INT4, seqno);
  Call_Write_DS(DB, fp_idx, filename, Nbytes, yyyymmdd, DATATYPE_YYYYMMDD, date);
  Call_Write_DS(DB, fp_idx, filename, Nbytes, hhmmss, DATATYPE_HHMMSS, time);
  Call_Write_DS(DB, fp_idx, filename, Nbytes, string, DATATYPE_STRING, statid);
  Call_Write_DS(DB, fp_idx, filename, Nbytes, pk9real, DATATYPE_REAL8, lat);
  Call_Write_DS(DB, fp_idx, filename, Nbytes, pk9real, DATATYPE_REAL8, lon);
  Call_Write_DS(DB, fp_idx, filename, Nbytes, linkoffset_t, DATATYPE_LINKOFFSET, LINKOFFSET(body));
  Call_Write_DS(DB, fp_idx, filename, Nbytes, linklen_t, DATATYPE_LINKLEN, LINKLEN(body));
PostStoreTable(hdr)

DefineLookupTable(hdr)

PUBLIC void
DB_Dim_T_hdr(void *T, int *Nrows, int *Ncols,
  int *Nrowoffset, int ProcID)
{
  TABLE_hdr *P = T;
  Call_LookupTable(hdr, P, Nrows, Ncols);
  if (Nrowoffset) *Nrowoffset = 0;
}

PUBLIC void
DB_Swapout_T_hdr(void *T)
{
  TABLE_hdr *P = T;
  int Nbytes = 0;
  int Count = 0;
  int PoolNo = P->PoolNo;
  FILE *do_trace = NULL;
  if (P->Swapped_out || !P->Is_loaded) return;
  do_trace = ODB_trace_fp();
  FreeDS(P, seqno, Nbytes, Count);
  FreeDS(P, date, Nbytes, Count);
  FreeDS(P, time, Nbytes, Count);
  FreeDS(P, statid, Nbytes, Count);
  FreeDS(P, lat, Nbytes, Count);
  FreeDS(P, lon, Nbytes, Count);
  FreeDS(P, LINKOFFSET(body), Nbytes, Count);
  FreeDS(P, LINKLEN(body), Nbytes, Count);
  P->Nrows = 0;
  P->Nalloc = 0;
  P->Is_loaded = 0;
  P->Swapped_out = P->Is_new ? 0 : 1;
  ODBMAC_TRACE_SWAPOUT(hdr,8);
}

DefineRemoveTable(DB, hdr)

PUBLIC int
DB_Sql_T_hdr(FILE *fp, int mode, const char *prefix, const char *postfix, char **sqlout) { ODBMAC_TABLESQL(); }

PUBLIC void *
DB_Init_T_hdr(void *T, ODB_Pool *Pool, int Is_new, int IO_method, int it, int dummy)
{
  TABLE_hdr *P = T;
  int PoolNo = Pool->poolno;
  ODB_Funcs *pf;
  static ODB_CommonFuncs *pfcom = NULL; /* Shared between pools & threads */
  DRHOOK_START(DB_Init_T_hdr);
  if (!P) ALLOC(P, 1);
  PreInitTable(P, 8);
  InitDS(pk1int, DATATYPE_INT4, seqno, hdr, 1);
  InitDS(yyyymmdd, DATATYPE_YYYYMMDD, date, hdr, 1);
  InitDS(hhmmss, DATATYPE_HHMMSS, time, hdr, 1);
  InitDS(string, DATATYPE_STRING, statid, hdr, 3);
  InitDS(pk9real, DATATYPE_REAL8, lat, hdr, 9);
  InitDS(pk9real, DATATYPE_REAL8, lon, hdr, 9);
  InitDS(linkoffset_t, DATATYPE_LINKOFFSET, LINKOFFSET(body), hdr, 1);
  InitDS(linklen_t, DATATYPE_LINKLEN, LINKLEN(body), hdr, 1);
  if (!pfcom) { /* Initialize once only */
    CALLOC(pfcom,1);
    { static char s[] = "@hdr"; pfcom->name = s; }
    pfcom->is_table = 1;
    pfcom->is_considered = 0;
    pfcom->ntables = 0;
    pfcom->ncols = 8;
    pfcom->tableno = 0;
    pfcom->rank = 0;
    pfcom->wt = 0.000000;
    pfcom->tags = DB_Set_T_hdr_TAG(&pfcom->ntag, &pfcom->nmem);
    pfcom->preptags = DB_Set_T_hdr_PREPTAG(&pfcom->npreptag);
    pfcom->Info = NULL;
    pfcom->create_index = 0;
    pfcom->init = DB_Init_T_hdr;
    pfcom->swapout = DB_Swapout_T_hdr;
    pfcom->dim = DB_Dim_T_hdr;
    pfcom->sortkeys = NULL;
    pfcom->update_info = NULL;
    pfcom->aggr_info = NULL;
    pfcom->getindex = NULL; /* N/A */
    pfcom->putindex = NULL; /* N/A */
    pfcom->select = DB_Sel_T_hdr;
    pfcom->remove = DB_Remove_T_hdr;
    pfcom->peinfo = NULL; /* N/A */
    pfcom->cancel = NULL;
    pfcom->dget = DB_dGet_T_hdr; /* REAL(8) dbmgr */
    pfcom->dput = DB_dPut_T_hdr; /* REAL(8) dbmgr */
    pfcom->load = DB_Load_T_hdr;
    pfcom->store = DB_Store_T_hdr;
    pfcom->pack = DB_Pack_T_hdr;
    pfcom->unpack = DB_Unpack_T_hdr;
    pfcom->sql = DB_Sql_T_hdr;
    pfcom->ncols_aux = 0;
    pfcom->colaux = NULL;
    pfcom->has_select_distinct = 0;
    pfcom->has_usddothash = 0;
  } /* if (!pfcom) */
  ALLOC(pf, 1);
  pf->it = it;
  pf->data = P;
  pf->Res = NULL;
  pf->tmp = NULL;
  pf->pool = Pool;
  pf->common = pfcom;
  pf->next = NULL;
  P->Funcs = pf;
  P->Handle = P->Funcs->pool->handle;
  DRHOOK_END(0);
  return P;
}

/* *************** End of TABLE "hdr" *************** */
