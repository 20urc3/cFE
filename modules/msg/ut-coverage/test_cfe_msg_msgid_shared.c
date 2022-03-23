/*
 * Test MsgId shared accessors
 */

/*
 * Includes
 */
#include "utassert.h"
#include "ut_support.h"
#include "cfe_msg.h"
#include "test_msg_not.h"
#include "test_msg_utils.h"
#include "test_cfe_msg_msgid_shared.h"
#include "cfe_error.h"
#include <string.h>

void Test_MSG_GetTypeFromMsgId(void)
{
    CFE_MSG_Message_t msg;
    CFE_SB_MsgId_t    msgid  = CFE_SB_INVALID_MSG_ID;
    CFE_MSG_Type_t    actual = CFE_MSG_Type_Invalid;

    UtPrintf("Bad parameter tests, Null pointer");
    memset(&msg, 0, sizeof(msg));
    UtAssert_INT32_EQ(CFE_MSG_GetTypeFromMsgId(msgid, NULL), CFE_MSG_BAD_ARGUMENT);
    UtAssert_INT32_EQ(Test_MSG_NotZero(&msg), 0);

    UtPrintf("Bad parameter tests, Invalid message ID");
    UtAssert_INT32_EQ(CFE_MSG_GetTypeFromMsgId(CFE_SB_ValueToMsgId(-1), &actual), CFE_MSG_BAD_ARGUMENT);

    UtPrintf("Set to all F's, test cmd and tlm");
    memset(&msg, 0xFF, sizeof(msg));
    CFE_UtAssert_SUCCESS(CFE_MSG_SetMsgId(&msg, CFE_SB_ValueToMsgId(CFE_PLATFORM_SB_HIGHEST_VALID_MSGID)));
    CFE_UtAssert_SUCCESS(CFE_MSG_SetType(&msg, CFE_MSG_Type_Tlm));
    CFE_UtAssert_SUCCESS(CFE_MSG_GetMsgId(&msg, &msgid));
    CFE_UtAssert_SUCCESS(CFE_MSG_GetTypeFromMsgId(msgid, &actual));
    UtAssert_INT32_EQ(actual, CFE_MSG_Type_Tlm);

    CFE_UtAssert_SUCCESS(CFE_MSG_SetType(&msg, CFE_MSG_Type_Cmd));
    CFE_UtAssert_SUCCESS(CFE_MSG_GetMsgId(&msg, &msgid));
    CFE_UtAssert_SUCCESS(CFE_MSG_GetTypeFromMsgId(msgid, &actual));
    UtAssert_INT32_EQ(actual, CFE_MSG_Type_Cmd);

    UtPrintf("Set to all 0, test cmd and tlm");
    CFE_UtAssert_SUCCESS(CFE_MSG_SetType(&msg, CFE_MSG_Type_Cmd));
    CFE_UtAssert_SUCCESS(CFE_MSG_GetMsgId(&msg, &msgid));
    CFE_UtAssert_SUCCESS(CFE_MSG_GetTypeFromMsgId(msgid, &actual));
    UtAssert_INT32_EQ(actual, CFE_MSG_Type_Cmd);

    CFE_UtAssert_SUCCESS(CFE_MSG_SetType(&msg, CFE_MSG_Type_Tlm));
    CFE_UtAssert_SUCCESS(CFE_MSG_GetMsgId(&msg, &msgid));
    CFE_UtAssert_SUCCESS(CFE_MSG_GetTypeFromMsgId(msgid, &actual));
    UtAssert_INT32_EQ(actual, CFE_MSG_Type_Tlm);
}

/*
 * Test MSG MsgId Shared
 */
void Test_MSG_MsgId_Shared(void)
{
    MSG_UT_ADD_SUBTEST(Test_MSG_GetTypeFromMsgId);
}
