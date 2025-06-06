/*
 * This file was generated by mib2c and is intended for use as
 * a mib module for the ucd-snmp snmpd agent. 
 *
 * Portions of this file are copyrighted by:
 * Copyright (c) 2016 VMware, Inc. All rights reserved.
 * Use is subject to license terms specified in the COPYING file
 * distributed with the Net-SNMP package.
 */


/*
 * This should always be included first before anything else 
 */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-features.h>

#include <sys/types.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif

/*
 * minimal include directives 
 */
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include "agent_global_vars.h"
#include "header_complex.h"
#include "snmpNotifyTable.h"
#include "snmpNotifyFilterProfileTable.h"
#include "target/snmpTargetParamsEntry.h"
#include "target/snmpTargetAddrEntry.h"
#include "target/target.h"
#include "snmp-notification-mib/snmpNotifyFilterTable/snmpNotifyFilterTable.h"
#include <net-snmp/agent/agent_callbacks.h>
#include <net-snmp/agent/agent_trap.h>
#include <net-snmp/agent/mib_module_config.h>
#include "net-snmp/agent/sysORTable.h"

#ifdef USING_NOTIFICATION_LOG_MIB_NOTIFICATION_LOG_MODULE
#   include "notification-log-mib/notification_log.h"
#endif

#ifndef NETSNMP_NO_WRITE_SUPPORT
netsnmp_feature_require(header_complex_find_entry);
#endif /* NETSNMP_NO_WRITE_SUPPORT */

/*
 * snmpNotifyTable_variables_oid:
 *   this is the top level oid that we want to register under.  This
 *   is essentially a prefix, with the suffix appearing in the
 *   variable below.
 */


oid             snmpNotifyTable_variables_oid[] =
    { 1, 3, 6, 1, 6, 3, 13, 1, 1 };

static oid snmpNotifyFullCompliance[] =
    { SNMP_OID_SNMPMODULES, 13, 3, 1, 3 }; /* SNMP-NOTIFICATION-MIB::snmpNotifyFullCompliance */


/*
 * variable2 snmpNotifyTable_variables:
 *   this variable defines function callbacks and type return information 
 *   for the snmpNotifyTable mib section 
 */


struct variable2 snmpNotifyTable_variables[] = {
    /*
     * magic number        , variable type , ro/rw , callback fn  , L, oidsuffix 
     */
#define   SNMPNOTIFYTAG         4
    {SNMPNOTIFYTAG, ASN_OCTET_STR, NETSNMP_OLDAPI_RWRITE,
     var_snmpNotifyTable, 2, {1, 2}},
#define   SNMPNOTIFYTYPE        5
    {SNMPNOTIFYTYPE, ASN_INTEGER, NETSNMP_OLDAPI_RWRITE,
     var_snmpNotifyTable, 2, {1, 3}},
#define   SNMPNOTIFYSTORAGETYPE  6
    {SNMPNOTIFYSTORAGETYPE, ASN_INTEGER, NETSNMP_OLDAPI_RWRITE,
     var_snmpNotifyTable, 2, {1, 4}},
#define   SNMPNOTIFYROWSTATUS   7
    {SNMPNOTIFYROWSTATUS, ASN_INTEGER, NETSNMP_OLDAPI_RWRITE,
     var_snmpNotifyTable, 2, {1, 5}},

};
/*
 * (L = length of the oidsuffix) 
 */


/*
 * init_snmpNotifyTable():
 *   Initialization routine.  This is called when the agent starts up.
 *   At a minimum, registration of your variables should take place here.
 */
void
init_snmpNotifyTable(void)
{
    DEBUGMSGTL(("snmpNotifyTable", "initializing...  "));

    init_snmpNotifyTable_data();

    /*
     * register ourselves with the agent to handle our mib tree 
     */
    REGISTER_MIB("snmpNotifyTable", snmpNotifyTable_variables, variable2,
                 snmpNotifyTable_variables_oid);


    /*
     * register our config handler(s) to deal with registrations 
     */
    snmpd_register_config_handler("snmpNotifyTable", parse_snmpNotifyTable,
                                  NULL, NULL);


    /*
     * place any other initialization junk you need here 
     */

    REGISTER_SYSOR_ENTRY(snmpNotifyFullCompliance,
        "The MIB modules for managing SNMP Notification, plus filtering.");

    DEBUGMSGTL(("snmpNotifyTable", "done.\n"));
}

void
shutdown_snmpNotifyTable(void)
{
    DEBUGMSGTL(("snmpNotifyTable", "shutting down ... "));

    shutdown_snmpNotifyTable_data();

    UNREGISTER_SYSOR_ENTRY(snmpNotifyFullCompliance);

    DEBUGMSGTL(("snmpNotifyTable", "done.\n"));
}


/*
 * parse_snmpNotifyTable():
 *   parses .conf file entries needed to configure the mib.
 */
void
parse_snmpNotifyTable(const char *token, char *line)
{
    size_t          tmpint;
    struct snmpNotifyTable_data *StorageTmp =
        SNMP_MALLOC_STRUCT(snmpNotifyTable_data);


    DEBUGMSGTL(("snmpNotifyTable", "parsing config...  "));


    if (StorageTmp == NULL) {
        config_perror("malloc failure");
        return;
    }

    line =
        read_config_read_data(ASN_OCTET_STR, line,
                              &StorageTmp->snmpNotifyName,
                              &StorageTmp->snmpNotifyNameLen);
    if (StorageTmp->snmpNotifyName == NULL) {
        config_perror("invalid specification for snmpNotifyName");
        SNMP_FREE(StorageTmp);
        return;
    }

    line =
        read_config_read_data(ASN_OCTET_STR, line,
                              &StorageTmp->snmpNotifyTag,
                              &StorageTmp->snmpNotifyTagLen);
    if (StorageTmp->snmpNotifyTag == NULL) {
        config_perror("invalid specification for snmpNotifyTag");
        SNMP_FREE(StorageTmp);
        return;
    }

    line =
        read_config_read_data(ASN_INTEGER, line,
                              &StorageTmp->snmpNotifyType, &tmpint);

    line =
        read_config_read_data(ASN_INTEGER, line,
                              &StorageTmp->snmpNotifyStorageType, &tmpint);
    if (!StorageTmp->snmpNotifyStorageType)
        StorageTmp->snmpNotifyStorageType = ST_READONLY;

    line =
        read_config_read_data(ASN_INTEGER, line,
                              &StorageTmp->snmpNotifyRowStatus, &tmpint);
    if (!StorageTmp->snmpNotifyRowStatus)
        StorageTmp->snmpNotifyRowStatus = RS_ACTIVE;


    if (snmpNotifyTable_add(StorageTmp) != SNMPERR_SUCCESS){
        SNMP_FREE(StorageTmp->snmpNotifyName);
        SNMP_FREE(StorageTmp->snmpNotifyTag);
        SNMP_FREE(StorageTmp);
    }


    DEBUGMSGTL(("snmpNotifyTable", "done.\n"));
}




/*
 * var_snmpNotifyTable():
 *   Handle this table separately from the scalar value case.
 *   The workings of this are basically the same as for var_snmpNotifyTable above.
 */
unsigned char  *
var_snmpNotifyTable(struct variable *vp,
                    oid * name,
                    size_t * length,
                    int exact,
                    size_t * var_len, WriteMethod ** write_method)
{
    struct snmpNotifyTable_data *StorageTmp = NULL;
    int             found = 1;

    DEBUGMSGTL(("snmpNotifyTable",
                "var_snmpNotifyTable: Entering...  \n"));
    /*
     * this assumes you have registered all your data properly
     */
    if ((StorageTmp = find_row_notifyTable(vp, name, length, exact,
                                           var_len, write_method)) == NULL) {
        found = 0;
    }

    switch (vp->magic) {
#ifndef NETSNMP_NO_WRITE_SUPPORT
    case SNMPNOTIFYTAG:
        *write_method = write_snmpNotifyTag;
        break;
    case SNMPNOTIFYTYPE:
        *write_method = write_snmpNotifyType;
        break;
    case SNMPNOTIFYSTORAGETYPE:
        *write_method = write_snmpNotifyStorageType;
        break;
    case SNMPNOTIFYROWSTATUS:
        *write_method = write_snmpNotifyRowStatus;
        break;
#endif /* !NETSNMP_NO_WRITE_SUPPORT */
    default:
        *write_method = NULL;
    }

    if (!found) {
        return NULL;
    }

#ifndef NETSNMP_NO_READ_SUPPORT
    switch (vp->magic) {
    case SNMPNOTIFYTAG:
        *var_len = StorageTmp->snmpNotifyTagLen;
        return (u_char *) StorageTmp->snmpNotifyTag;

    case SNMPNOTIFYTYPE:
        *var_len = sizeof(StorageTmp->snmpNotifyType);
        return (u_char *) & StorageTmp->snmpNotifyType;

    case SNMPNOTIFYSTORAGETYPE:
        *var_len = sizeof(StorageTmp->snmpNotifyStorageType);
        return (u_char *) & StorageTmp->snmpNotifyStorageType;

    case SNMPNOTIFYROWSTATUS:
        *var_len = sizeof(StorageTmp->snmpNotifyRowStatus);
        return (u_char *) & StorageTmp->snmpNotifyRowStatus;

    default:
        ERROR_MSG("");
    }
#endif /* !NETSNMP_NO_READ_SUPPORT */ 
    return NULL;
}

static int
is_delim(const char c)
{
    return (c == 0x020 || c == 0x09 || c == 0x0d || c == 0x0b);
}

int
snmpTagValid(const char *tag, const size_t tagLen)
{
    size_t          i = 0;


    for (i = 0; i < tagLen; i++) {
        if (is_delim(tag[i])) {
            /*
             * Delimeters aren't allowed.  
             */
            return 0;
        }
    }
    return 1;
}

#ifndef NETSNMP_NO_WRITE_SUPPORT

static struct snmpNotifyTable_data *StorageNew;

static const int snmpNotifyTable_offset =
    OID_LENGTH(snmpNotifyTable_variables_oid) + 3 - 1;

int
write_snmpNotifyTag(int action,
                    u_char * var_val,
                    u_char var_val_type,
                    size_t var_val_len,
                    u_char * statP, oid * name, size_t name_len)
{
    static char    *tmpvar;
    struct snmpNotifyTable_data *StorageTmp = NULL;
    static size_t   tmplen;
    size_t          newlen = name_len - snmpNotifyTable_offset;


    DEBUGMSGTL(("snmpNotifyTable",
                "write_snmpNotifyTag entering action=%d...  \n", action));
    if (action != RESERVE1 &&
        (StorageTmp = find_row_notifyTable(NULL, &name[snmpNotifyTable_offset],
                                           &newlen, 1, NULL, NULL)) == NULL) {
        if ((StorageTmp = StorageNew) == NULL)
            return SNMP_ERR_NOSUCHNAME; /* remove if you support creation here */
    }


    switch (action) {
    case RESERVE1:
        if (var_val_type != ASN_OCTET_STR) {
            return SNMP_ERR_WRONGTYPE;
        }
        if (var_val_len > 255) {
            return SNMP_ERR_WRONGLENGTH;
        }
        if (!snmpTagValid((char *) var_val, var_val_len)) {
            return SNMP_ERR_WRONGVALUE;
        }
        break;


    case RESERVE2:
        /*
         * memory reseveration, final preparation... 
         */
        tmpvar = StorageTmp->snmpNotifyTag;
        tmplen = StorageTmp->snmpNotifyTagLen;
        StorageTmp->snmpNotifyTag = calloc(1, var_val_len + 1);
        if (NULL == StorageTmp->snmpNotifyTag)
            return SNMP_ERR_RESOURCEUNAVAILABLE;
        break;


    case FREE:
        /*
         * Release any resources that have been allocated 
         */
        break;


    case ACTION:
        memcpy(StorageTmp->snmpNotifyTag, var_val, var_val_len);
        StorageTmp->snmpNotifyTagLen = var_val_len;
        break;


    case UNDO:
        /*
         * Back out any changes made in the ACTION case 
         */
        SNMP_FREE(StorageTmp->snmpNotifyTag);
        StorageTmp->snmpNotifyTag = tmpvar;
        StorageTmp->snmpNotifyTagLen = tmplen;
        tmpvar = NULL;
        break;


    case COMMIT:
        /*
         * Things are working well, so it's now safe to make the change
         * permanently.  Make sure that anything done here can't fail! 
         */
        SNMP_FREE(tmpvar);
        snmp_store_needed(NULL);
        break;
    }

    return SNMP_ERR_NOERROR;
}



int
write_snmpNotifyType(int action,
                     u_char * var_val,
                     u_char var_val_type,
                     size_t var_val_len,
                     u_char * statP, oid * name, size_t name_len)
{
    static int      tmpvar;
    struct snmpNotifyTable_data *StorageTmp = NULL;
    long            value = *((long *) var_val);
    size_t          newlen = name_len - snmpNotifyTable_offset;


    DEBUGMSGTL(("snmpNotifyTable",
                "write_snmpNotifyType entering action=%d...  \n", action));
    if (action != RESERVE1 &&
        (StorageTmp = find_row_notifyTable(NULL, &name[snmpNotifyTable_offset],
                                           &newlen, 1, NULL, NULL)) == NULL) {
        if ((StorageTmp = StorageNew) == NULL)
            return SNMP_ERR_NOSUCHNAME;
    }

    switch (action) {
    case RESERVE1:
        if (var_val_type != ASN_INTEGER) {
            return SNMP_ERR_WRONGTYPE;
        }
        if (var_val_len != sizeof(long)) {
            return SNMP_ERR_WRONGLENGTH;
        }
        if (value < 1 || value > 2) {
            return SNMP_ERR_WRONGVALUE;
        }
        break;

    case ACTION:
        tmpvar = StorageTmp->snmpNotifyType;
        StorageTmp->snmpNotifyType = value;
        break;

    case UNDO:
        /*
         * Back out any changes made in the ACTION case 
         */
        StorageTmp->snmpNotifyType = tmpvar;
        break;
    }

    return SNMP_ERR_NOERROR;
}



int
write_snmpNotifyStorageType(int action,
                            u_char * var_val,
                            u_char var_val_type,
                            size_t var_val_len,
                            u_char * statP, oid * name, size_t name_len)
{
    static int      tmpvar;
    long            value = *((long *) var_val);
    struct snmpNotifyTable_data *StorageTmp = NULL;
    size_t          newlen = name_len - snmpNotifyTable_offset;


    DEBUGMSGTL(("snmpNotifyTable",
                "write_snmpNotifyStorageType entering action=%d...  \n",
                action));
    if (action != RESERVE1 &&
        (StorageTmp = find_row_notifyTable(NULL, &name[snmpNotifyTable_offset],
                                           &newlen, 1, NULL, NULL)) == NULL) {
        if ((StorageTmp = StorageNew) == NULL)
            return SNMP_ERR_NOSUCHNAME;
    }


    switch (action) {
    case RESERVE1:
        if (var_val_type != ASN_INTEGER) {
            return SNMP_ERR_WRONGTYPE;
        }
        if (var_val_len != sizeof(long)) {
            return SNMP_ERR_WRONGLENGTH;
        }
        if (value != SNMP_STORAGE_OTHER && value != SNMP_STORAGE_VOLATILE
            && value != SNMP_STORAGE_NONVOLATILE) {
            return SNMP_ERR_WRONGVALUE;
        }
        break;

    case ACTION:
        tmpvar = StorageTmp->snmpNotifyStorageType;
        StorageTmp->snmpNotifyStorageType = value;
        break;

    case UNDO:
        StorageTmp->snmpNotifyStorageType = tmpvar;
        break;
    }
    return SNMP_ERR_NOERROR;
}



int
write_snmpNotifyRowStatus(int action,
                          u_char * var_val,
                          u_char var_val_type,
                          size_t var_val_len,
                          u_char * statP, oid * name, size_t name_len)
{
    struct snmpNotifyTable_data *StorageTmp = NULL;
    static struct snmpNotifyTable_data *StorageDel;
    size_t          newlen = name_len - snmpNotifyTable_offset;
    static int      old_value;
    int             set_value = *((long *) var_val);
    static netsnmp_variable_list *vars, *vp;

    DEBUGMSGTL(("snmpNotifyTable",
                "write_snmpNotifyRowStatus entering action=%d...  \n",
                action));
    StorageTmp = find_row_notifyTable(NULL, &name[snmpNotifyTable_offset],
                                      &newlen, 1, NULL, NULL);

    switch (action) {
    case RESERVE1:
        if (var_val_type != ASN_INTEGER || var_val == NULL) {
            return SNMP_ERR_WRONGTYPE;
        }
        if (var_val_len != sizeof(long)) {
            return SNMP_ERR_WRONGLENGTH;
        }
        if (set_value < 1 || set_value > 6 || set_value == RS_NOTREADY) {
            return SNMP_ERR_WRONGVALUE;
        }
        if (StorageTmp == NULL) {
            /*
             * create the row now? 
             */
            /*
             * ditch illegal values now 
             */
            if (set_value == RS_ACTIVE || set_value == RS_NOTINSERVICE) {
                return SNMP_ERR_INCONSISTENTVALUE;
            }
        } else {
            /*
             * row exists.  Check for a valid state change 
             */
            if (set_value == RS_CREATEANDGO
                || set_value == RS_CREATEANDWAIT) {
                /*
                 * can't create a row that exists 
                 */
                return SNMP_ERR_INCONSISTENTVALUE;
            }
            /*
             * XXX: interaction with row storage type needed 
             */
        }

        /*
         * memory reseveration, final preparation... 
         */
        if (StorageTmp == NULL &&
            (set_value == RS_CREATEANDGO
             || set_value == RS_CREATEANDWAIT)) {
            /*
             * creation 
             */
            vars = NULL;

            snmp_varlist_add_variable(&vars, NULL, 0, ASN_PRIV_IMPLIED_OCTET_STR, NULL, 0);     /* snmpNotifyName */

            if (header_complex_parse_oid
                (&
                 (name
                  [OID_LENGTH(snmpNotifyTable_variables_oid) +
                   2]), newlen, vars) != SNMPERR_SUCCESS) {
                /*
                 * XXX: free, zero vars 
                 */
                snmp_free_var(vars);
                return SNMP_ERR_INCONSISTENTNAME;
            }
            vp = vars;


            StorageNew = SNMP_MALLOC_STRUCT(snmpNotifyTable_data);
            if (StorageNew == NULL) {
                return SNMP_ERR_RESOURCEUNAVAILABLE;
            }
            StorageNew->snmpNotifyName = calloc( 1, vp->val_len + 1 );
            if (StorageNew->snmpNotifyName == NULL) {
                return SNMP_ERR_RESOURCEUNAVAILABLE;
            }
            memcpy(StorageNew->snmpNotifyName, vp->val.string, vp->val_len);
            StorageNew->snmpNotifyNameLen = vp->val_len;
            vp = vp->next_variable;

            /*
             * default values 
             */
            StorageNew->snmpNotifyStorageType = ST_NONVOLATILE;
            StorageNew->snmpNotifyType = SNMPNOTIFYTYPE_TRAP;
            StorageNew->snmpNotifyTagLen = 0;
            StorageNew->snmpNotifyTag = calloc(1, sizeof(char));
            if (StorageNew->snmpNotifyTag == NULL) {
                return SNMP_ERR_RESOURCEUNAVAILABLE;
            }

            StorageNew->snmpNotifyRowStatus = set_value;
            snmp_free_var(vars);
        }
        break;

    case RESERVE2:
        break;

    case FREE:
        if (StorageNew != NULL) {
            SNMP_FREE(StorageNew->snmpNotifyTag);
            SNMP_FREE(StorageNew->snmpNotifyName);
            free(StorageNew);
            StorageNew = NULL;
        }
        break;

    case ACTION:
        if (StorageTmp == NULL && (set_value == RS_CREATEANDGO ||
                                   set_value == RS_CREATEANDWAIT)) {
            /*
             * row creation, so add it 
             */
            if (StorageNew != NULL) {
                snmpNotifyTable_add(StorageNew);
            }
        } else if (set_value != RS_DESTROY) {
            /*
             * set the flag? 
             */
            if (StorageTmp == NULL)
                return SNMP_ERR_GENERR; /* should never ever get here */
            
            old_value = StorageTmp->snmpNotifyRowStatus;
            StorageTmp->snmpNotifyRowStatus = *((long *) var_val);
        } else {
            /*
             * destroy...  extract it for now 
             */
            if (StorageTmp)
                StorageDel = snmpNotifyTable_extract(StorageTmp);
        }
        break;

    case UNDO:
        /*
         * Back out any changes made in the ACTION case 
         */
        if (StorageTmp == NULL && (set_value == RS_CREATEANDGO ||
                                   set_value == RS_CREATEANDWAIT)) {
            /*
             * row creation, so remove it again 
             */
            StorageDel = snmpNotifyTable_extract(StorageNew);
            /*
             * XXX: free it 
             */
        } else if (StorageDel != NULL) {
            /*
             * row deletion, so add it again 
             */
            snmpNotifyTable_add(StorageDel);
        } else if (set_value != RS_DESTROY) {
            if (StorageTmp)
                StorageTmp->snmpNotifyRowStatus = old_value;
        }
        break;

    case COMMIT:
        if (StorageDel != NULL) {
            snmpNotifyTable_dispose(StorageDel);
            StorageDel = NULL;
        }
        if (StorageTmp
            && StorageTmp->snmpNotifyRowStatus == RS_CREATEANDGO) {
            StorageTmp->snmpNotifyRowStatus = RS_ACTIVE;
            StorageNew = NULL;
        } else if (StorageTmp &&
                   StorageTmp->snmpNotifyRowStatus == RS_CREATEANDWAIT) {
            StorageTmp->snmpNotifyRowStatus = RS_NOTINSERVICE;
            StorageNew = NULL;
        }
        snmp_store_needed(NULL);
        break;
    }
    return SNMP_ERR_NOERROR;
}
#endif /* !NETSNMP_NO_WRITE_SUPPORT */
