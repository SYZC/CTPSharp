
#include "stdafx.h"
#include "TradeApi.h"
#include "..\api\x86\ThostFtdcUserApiDataType.h"
#include "..\api\x86\ThostFtdcUserApiStruct.h"

#pragma region ���󷽷�

//��ȡ�ӿڰ汾
TRADEAPI_API const char* GetApiVersion()
{
	return CThostFtdcTraderApi::GetApiVersion();
}

//�����ص���
TRADEAPI_API CTraderSpi* CreateSpi()
{
	CTraderSpi* pUserSpi = new CTraderSpi();
	return pUserSpi;
}

//����
TRADEAPI_API CThostFtdcTraderApi* Connect(char *frontAddr, char *pszFlowPath, CTraderSpi* pUserSpi)
{
	// ��ʼ��UserApi
	CThostFtdcTraderApi* pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath);			// ����UserApi	
																									//CTraderSpi* pUserSpi = new CTraderSpi();
	pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// ע���¼���
	pUserApi->SubscribePublicTopic(THOST_TERT_QUICK/*THOST_TERT_RESTART*/);					// ע�ṫ����
	pUserApi->SubscribePrivateTopic(THOST_TERT_QUICK/*THOST_TERT_RESTART*/);					// ע��˽����
	pUserApi->RegisterFront(frontAddr);							// connect
	pUserApi->Init();
	//pUserApi->Join();
	return pUserApi;
}

//�Ͽ�
TRADEAPI_API void DisConnect(CThostFtdcTraderApi* pUserApi)
{
	if (pUserApi == NULL) return;

	pUserApi->RegisterSpi(NULL);
	pUserApi->Release();
	pUserApi = NULL;
}

//��ȡ������
TRADEAPI_API const char* GetTradingDay(CThostFtdcTraderApi* pUserApi)
{
	if (pUserApi == NULL) return NULL;

	return pUserApi->GetTradingDay();
}

//�ͻ�����֤����
TRADEAPI_API int ReqAuthenticate(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID, TThostFtdcProductInfoType productInfo, TThostFtdcAuthCodeType authCode)
{
	if (pUserApi == NULL) return NULL;

	CThostFtdcReqAuthenticateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.UserID, userID);
	strcpy_s(req.UserProductInfo, productInfo);
	strcpy_s(req.AuthCode, authCode);
	return pUserApi->ReqAuthenticate(&req, requestID);
}

//�����û���¼����
TRADEAPI_API int ReqUserLogin(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID, TThostFtdcPasswordType password)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.UserID, userID);
	strcpy_s(req.Password, password);
	strcpy_s(req.UserProductInfo, "HF");
	return pUserApi->ReqUserLogin(&req, requestID);
}
//���͵ǳ�����
TRADEAPI_API int ReqUserLogout(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType investorID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcUserLogoutField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.UserID, investorID);
	return pUserApi->ReqUserLogout(&req, requestID);
}
//�����û�����
TRADEAPI_API int ReqUserPasswordUpdate(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID, TThostFtdcUserIDType oldPassword, TThostFtdcPasswordType newPassword)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcUserPasswordUpdateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.UserID, userID);
	strcpy_s(req.OldPassword, oldPassword);
	strcpy_s(req.NewPassword, newPassword);
	return pUserApi->ReqUserPasswordUpdate(&req, requestID);
}
//�ʽ��˻������������
TRADEAPI_API int ReqTradingAccountPasswordUpdate(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcAccountIDType accountID, TThostFtdcUserIDType oldPassword, TThostFtdcPasswordType newPassword)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcTradingAccountPasswordUpdateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.AccountID, accountID);
	strcpy_s(req.NewPassword, newPassword);
	strcpy_s(req.OldPassword, oldPassword);
	return pUserApi->ReqTradingAccountPasswordUpdate(&req, requestID);
}
//��ȫ��¼����
TRADEAPI_API int ReqUserSafeLogin(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID, TThostFtdcPasswordType password)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.UserID, userID);
	strcpy_s(req.Password, password);
	strcpy_s(req.UserProductInfo, "HF");
	return pUserApi->ReqUserLogin2(&req, requestID);
}
//��ȫ�����û�����
TRADEAPI_API int ReqUserPasswordSafeUpdate(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID, TThostFtdcUserIDType oldPassword, TThostFtdcPasswordType newPassword)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcUserPasswordUpdateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.UserID, userID);
	strcpy_s(req.OldPassword, oldPassword);
	strcpy_s(req.NewPassword, newPassword);
	return pUserApi->ReqUserPasswordUpdate2(&req, requestID);
}
//����¼������
TRADEAPI_API int ReqOrderInsert(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcInputOrderField *pOrder)
{
	if (pUserApi == NULL) return -1;

	int siez = sizeof(CThostFtdcInputOrderField);
	strcpy_s(pOrder->BusinessUnit, "HF");
	return pUserApi->ReqOrderInsert(pOrder, requestID);
}
//������������
TRADEAPI_API int ReqOrderAction(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcInputOrderActionField *pOrder)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqOrderAction(pOrder, requestID);
}
//��ѯ��󱨵���������
TRADEAPI_API int ReqQueryMaxOrderVolume(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQueryMaxOrderVolumeField *pMaxOrderVolume)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQueryMaxOrderVolume(pMaxOrderVolume, requestID);
}
//Ͷ���߽�����ȷ��
TRADEAPI_API int ReqSettlementInfoConfirm(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
{
	
	if (pUserApi == NULL) return -1;

	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	return pUserApi->ReqSettlementInfoConfirm(&req, requestID);
}
//ִ������¼������
TRADEAPI_API int ReqExecOrderInsert(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcInputExecOrderField *pInputExecOrder)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqExecOrderInsert(pInputExecOrder, requestID);
}
//ִ�������������
TRADEAPI_API int ReqExecOrderAction(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcInputExecOrderActionField *pInputExecOrderAction)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqExecOrderAction(pInputExecOrderAction, requestID);
}
//ѯ��¼������
TRADEAPI_API int ReqForQuoteInsert(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcInputForQuoteField *pInputForQuote)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqForQuoteInsert(pInputForQuote, requestID);
}
//����¼������
TRADEAPI_API int ReqQuoteInsert(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcInputQuoteField *pInputQuote)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQuoteInsert(pInputQuote, requestID);
}
//���۲�������
TRADEAPI_API int ReqQuoteAction(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcInputQuoteActionField *pInputQuoteAction)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQuoteAction(pInputQuoteAction, requestID);
}
//����������������
TRADEAPI_API int ReqBatchOrderAction(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqBatchOrderAction(pInputBatchOrderAction, requestID);
}
//��Ȩ�ԶԳ�¼������
TRADEAPI_API int ReqOptionSelfCloseInsert(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqOptionSelfCloseInsert(pInputOptionSelfClose, requestID);
}
//��Ȩ�ԶԳ��������
TRADEAPI_API int ReqOptionSelfCloseAction(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqOptionSelfCloseAction(pInputOptionSelfCloseAction, requestID);
}
//�������¼������
TRADEAPI_API int ReqCombActionInsert(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcInputCombActionField *pInputCombAction)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqCombActionInsert(pInputCombAction, requestID);
}
//�����ѯ����
TRADEAPI_API int ReqQryOrder(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQryOrderField *pQryOrder)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryOrder(pQryOrder, requestID);
}
//�����ѯ�ɽ�
TRADEAPI_API int ReqQryTrade(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQryTradeField *pQryTrade)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryTrade(pQryTrade, requestID);
}
//�����ѯͶ���ֲ߳�
TRADEAPI_API int ReqQryInvestorPosition(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	if (instrumentID != NULL)
		strcpy_s(req.InstrumentID, instrumentID);
	return pUserApi->ReqQryInvestorPosition(&req, requestID);
}
//�����ѯ�ʽ��˻�
TRADEAPI_API int ReqQryTradingAccount(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryTradingAccountField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	return pUserApi->ReqQryTradingAccount(&req, requestID);
}
//�����ѯͶ����
TRADEAPI_API int ReqQryInvestor(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryInvestorField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	return pUserApi->ReqQryInvestor(&req, requestID);
}
//�����ѯ���ױ���
TRADEAPI_API int ReqQryTradingCode(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcClientIDType clientID, TThostFtdcExchangeIDType	exchangeID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryTradingCodeField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	if (clientID != NULL)
		strcpy_s(req.ClientID, clientID);
	if (exchangeID != NULL)
		strcpy_s(req.ExchangeID, exchangeID);
	return pUserApi->ReqQryTradingCode(&req, requestID);
}
//�����ѯ��Լ��֤����
TRADEAPI_API int ReqQryInstrumentMarginRate(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID, TThostFtdcHedgeFlagType	hedgeFlag)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryInstrumentMarginRateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	if (instrumentID != NULL)
		strcpy_s(req.InstrumentID, instrumentID);
	if (hedgeFlag != NULL)
		req.HedgeFlag = hedgeFlag;						//*��*�ܲ���null�������в�ѯ
	return pUserApi->ReqQryInstrumentMarginRate(&req, requestID);
}
//�����ѯ��Լ��������
TRADEAPI_API int ReqQryInstrumentCommissionRate(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryInstrumentCommissionRateField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	if (instrumentID != NULL)
		strcpy_s(req.InstrumentID, instrumentID);
	return pUserApi->ReqQryInstrumentCommissionRate(&req, requestID);
}
//�����ѯ������
TRADEAPI_API int ReqQryExchange(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcExchangeIDType exchangeID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryExchangeField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.ExchangeID, exchangeID);
	return pUserApi->ReqQryExchange(&req, requestID);
}
//�����ѯ��Լ
TRADEAPI_API int ReqQryInstrument(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcInstrumentIDType instrumentID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
	if (instrumentID != NULL)
		strcpy_s(req.InstrumentID, instrumentID);
	return pUserApi->ReqQryInstrument(&req, requestID);
}
//�����ѯ����
TRADEAPI_API int ReqQryDepthMarketData(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcInstrumentIDType instrumentID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryDepthMarketDataField req;
	memset(&req, 0, sizeof(req));
	if (instrumentID != NULL)
		strcpy_s(req.InstrumentID, instrumentID);
	return pUserApi->ReqQryDepthMarketData(&req, requestID);
}
//�����ѯͶ���߽�����
TRADEAPI_API int ReqQrySettlementInfo(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcDateType	tradingDay)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQrySettlementInfoField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	if (tradingDay != NULL)
		strcpy_s(req.TradingDay, tradingDay);
	return pUserApi->ReqQrySettlementInfo(&req, requestID);
}
//��ѯ�ֲ���ϸ
TRADEAPI_API int ReqQryInvestorPositionDetail(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryInvestorPositionDetailField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	if (instrumentID != NULL)
		strcpy_s(req.InstrumentID, instrumentID);
	return pUserApi->ReqQryInvestorPositionDetail(&req, requestID);
}
//�����ѯ�ͻ�֪ͨ
TRADEAPI_API int ReqQryNotice(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryNoticeField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	return pUserApi->ReqQryNotice(&req, requestID);
}
//�����ѯ������Ϣȷ��
TRADEAPI_API int ReqQrySettlementInfoConfirm(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQrySettlementInfoConfirmField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	return pUserApi->ReqQrySettlementInfoConfirm(&req, requestID);
}
//�����ѯ**���**�ֲ���ϸ
TRADEAPI_API int ReqQryInvestorPositionCombineDetail(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryInvestorPositionCombineDetailField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	if (instrumentID != NULL)
		strcpy_s(req.CombInstrumentID, instrumentID);
	return pUserApi->ReqQryInvestorPositionCombineDetail(&req, requestID);
}
//�����ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ
TRADEAPI_API int ReqQryCFMMCTradingAccountKey(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryCFMMCTradingAccountKeyField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	return pUserApi->ReqQryCFMMCTradingAccountKey(&req, requestID);
}
//�����ѯ�ֵ��۵���Ϣ
TRADEAPI_API int ReqQryEWarrantOffset(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQryEWarrantOffsetField *pQryEWarrantOffset)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryEWarrantOffset(pQryEWarrantOffset, requestID);
}
//�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
TRADEAPI_API int ReqQryInvestorProductGroupMargin(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQryInvestorProductGroupMarginField *pQryInvestorProductGroupMargin)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryInvestorProductGroupMargin(pQryInvestorProductGroupMargin, requestID);
}
//�����ѯ��������֤����
TRADEAPI_API int ReqQryExchangeMarginRate(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInstrumentIDType instrumentID, TThostFtdcHedgeFlagType hedgeFlag)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryExchangeMarginRateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	if (instrumentID != NULL)
		strcpy_s(req.InstrumentID, instrumentID);
	req.HedgeFlag = hedgeFlag;
	return pUserApi->ReqQryExchangeMarginRate(&req, requestID);
}
//�����ѯ������������֤����
TRADEAPI_API int ReqQryExchangeMarginRateAdjust(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInstrumentIDType instrumentID, TThostFtdcHedgeFlagType hedgeFlag)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryExchangeMarginRateAdjustField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	if (instrumentID != NULL)
		strcpy_s(req.InstrumentID, instrumentID);
	req.HedgeFlag = hedgeFlag;
	return pUserApi->ReqQryExchangeMarginRateAdjust(&req, requestID);
}
//�����ѯ����
TRADEAPI_API int ReqQryExchangeRate(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQryExchangeRateField *pQryExchangeRate)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryExchangeRate(pQryExchangeRate, requestID);
}
//�����ѯ�����������Ա����Ȩ��
TRADEAPI_API int ReqQrySecAgentACIDMap(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQrySecAgentACIDMapField *pQrySecAgentACIDMap)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQrySecAgentACIDMap(pQrySecAgentACIDMap, requestID);
}
//�����ѯ��Ʒ���ۻ���
TRADEAPI_API int ReqQryProductExchRate(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcInstrumentIDType productID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryProductExchRateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.ProductID, productID);
	return pUserApi->ReqQryProductExchRate(&req, requestID);
}
//�����ѯ��Ʒ��
TRADEAPI_API int ReqQryProductGroup(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcInstrumentIDType productID, TThostFtdcExchangeIDType exchangeID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryProductGroupField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.ProductID, productID);
	strcpy_s(req.ExchangeID, exchangeID);
	return pUserApi->ReqQryProductGroup(&req, requestID);
}
//�����ѯ�����̺�Լ��������
TRADEAPI_API int ReqQryMMInstrumentCommissionRate(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryMMInstrumentCommissionRateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	if (instrumentID != NULL)
		strcpy_s(req.InstrumentID, instrumentID);
	return pUserApi->ReqQryMMInstrumentCommissionRate(&req, requestID);
}
//�����ѯ��������Ȩ��Լ������
TRADEAPI_API int ReqQryMMOptionInstrCommRate(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryMMOptionInstrCommRateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	if (instrumentID != NULL)
		strcpy_s(req.InstrumentID, instrumentID);
	return pUserApi->ReqQryMMOptionInstrCommRate(&req, requestID);
}
//�����ѯ����������
TRADEAPI_API int ReqQryInstrumentOrderCommRate(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryInstrumentOrderCommRateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	if (instrumentID != NULL)
		strcpy_s(req.InstrumentID, instrumentID);
	return pUserApi->ReqQryInstrumentOrderCommRate(&req, requestID);
}
//�����ѯ�ʽ��˻�
TRADEAPI_API int ReqQrySecAgentTradingAccount(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQryTradingAccountField *pQryTradingAccount)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQrySecAgentTradingAccount(pQryTradingAccount, requestID);
}
//�����ѯ�����������ʽ�У��ģʽ
TRADEAPI_API int ReqQrySecAgentCheckMode(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQrySecAgentCheckModeField *pQrySecAgentCheckMode)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQrySecAgentCheckMode(pQrySecAgentCheckMode, requestID);
}
//�����ѯ��Ȩ���׳ɱ�
TRADEAPI_API int ReqQryOptionInstrTradeCost(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQryOptionInstrTradeCostField *pQryOptionInstrTradeCost)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryOptionInstrTradeCost(pQryOptionInstrTradeCost, requestID);
}
//�����ѯ��Ȩ��Լ������
TRADEAPI_API int ReqQryOptionInstrCommRate(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryOptionInstrCommRateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	if (instrumentID != NULL)
		strcpy_s(req.InstrumentID, instrumentID);
	return pUserApi->ReqQryOptionInstrCommRate(&req, requestID);
}
//�����ѯִ������
TRADEAPI_API int ReqQryExecOrder(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQryExecOrderField *pQryExecOrder)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryExecOrder(pQryExecOrder, requestID);
}
//�����ѯѯ��
TRADEAPI_API int ReqQryForQuote(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQryForQuoteField *pQryForQuote)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryForQuote(pQryForQuote, requestID);
}
//�����ѯ����
TRADEAPI_API int ReqQryQuote(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQryQuoteField *pQryQuote)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryQuote(pQryQuote, requestID);
}
//�����ѯ��Ȩ�ԶԳ�
TRADEAPI_API int ReqQryOptionSelfClose(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQryOptionSelfCloseField *pQryOptionSelfClose)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryOptionSelfClose(pQryOptionSelfClose, requestID);
}
//�����ѯͶ�ʵ�Ԫ
TRADEAPI_API int ReqQryInvestUnit(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQryInvestUnitField *pQryInvestUnit)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryInvestUnit(pQryInvestUnit, requestID);
}
//�����ѯ��Ϻ�Լ��ȫϵ��
TRADEAPI_API int ReqQryCombInstrumentGuard(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQryCombInstrumentGuardField *pQryCombInstrumentGuard)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryCombInstrumentGuard(pQryCombInstrumentGuard, requestID);
}
//�����ѯ�������
TRADEAPI_API int ReqQryCombAction(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcQryCombActionField *pQryCombAction)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryCombAction(pQryCombAction, requestID);
}
//�����ѯ����֪ͨ
TRADEAPI_API int ReqQryTradingNotice(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryTradingNoticeField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	return pUserApi->ReqQryTradingNotice(&req, requestID);
}
//�����ѯ���͹�˾���ײ���
TRADEAPI_API int ReqQryBrokerTradingParams(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryBrokerTradingParamsField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	return pUserApi->ReqQryBrokerTradingParams(&req, requestID);
}
//�����ѯ���͹�˾�����㷨
TRADEAPI_API int ReqQryBrokerTradingAlgos(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcExchangeIDType exchangeID, TThostFtdcInstrumentIDType instrumentID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryBrokerTradingAlgosField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	if (exchangeID != NULL)
		strcpy_s(req.ExchangeID, exchangeID);
	if (instrumentID != NULL)
		strcpy_s(req.InstrumentID, instrumentID);

	return pUserApi->ReqQryBrokerTradingAlgos(&req, requestID);
}
//Ԥ��¼������
TRADEAPI_API int ReqParkedOrderInsert(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcParkedOrderField *ParkedOrder)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqParkedOrderInsert(ParkedOrder, requestID);
}
//Ԥ�񳷵�¼������
TRADEAPI_API int ReqParkedOrderAction(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcParkedOrderActionField *ParkedOrderAction)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqParkedOrderAction(ParkedOrderAction, requestID);
}
//����ɾ��Ԥ��
TRADEAPI_API int ReqRemoveParkedOrder(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcParkedOrderIDType parkedOrderID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcRemoveParkedOrderField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	strcpy_s(req.ParkedOrderID, parkedOrderID);
	return pUserApi->ReqRemoveParkedOrder(&req, requestID);
}
//����ɾ��Ԥ�񳷵�
TRADEAPI_API int ReqRemoveParkedOrderAction(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcParkedOrderActionIDType parkedOrderActionID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcRemoveParkedOrderActionField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	strcpy_s(req.ParkedOrderActionID, parkedOrderActionID);
	return pUserApi->ReqRemoveParkedOrderAction(&req, requestID);
}

//�����ѯת������
TRADEAPI_API int ReqQryTransferBank(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBankIDType bankID, TThostFtdcBankBrchIDType bankBrchID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryTransferBankField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BankID, bankID);
	strcpy_s(req.BankBrchID, bankBrchID);
	return pUserApi->ReqQryTransferBank(&req, requestID);
}
//�����ѯת����ˮ
TRADEAPI_API int ReqQryTransferSerial(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcAccountIDType accountID, TThostFtdcBankIDType bankID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryTransferSerialField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.AccountID, accountID);
	strcpy_s(req.BankID, bankID);
	return pUserApi->ReqQryTransferSerial(&req, requestID);
}
//�����ѯ����ǩԼ��ϵ
TRADEAPI_API int ReqQryAccountregister(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcAccountIDType accountID, TThostFtdcBankIDType bankID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryAccountregisterField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.AccountID, accountID);
	strcpy_s(req.BankID, bankID);
	return pUserApi->ReqQryAccountregister(&req, requestID);
}
//�����ѯǩԼ����
TRADEAPI_API int ReqQryContractBank(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcBankIDType bankID, TThostFtdcBankBrchIDType bankBrchID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryContractBankField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	if (bankID != NULL)
		strcpy_s(req.BankID, bankID);
	if (bankBrchID != NULL)
		strcpy_s(req.BankBrchID, bankBrchID);
	return pUserApi->ReqQryContractBank(&req, requestID);
}
//�����ѯԤ��
TRADEAPI_API int ReqQryParkedOrder(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID, TThostFtdcExchangeIDType exchangeID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryParkedOrderField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	if (instrumentID != NULL)
		strcpy_s(req.InstrumentID, instrumentID);
	if (exchangeID != NULL)
		strcpy_s(req.ExchangeID, exchangeID);
	return pUserApi->ReqQryParkedOrder(&req, requestID);
}
//�����ѯԤ�񳷵�
TRADEAPI_API int ReqQryParkedOrderAction(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID, TThostFtdcExchangeIDType exchangeID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQryParkedOrderActionField  req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	if (instrumentID != NULL)
		strcpy_s(req.InstrumentID, instrumentID);
	if (exchangeID != NULL)
		strcpy_s(req.ExchangeID, exchangeID);
	return pUserApi->ReqQryParkedOrderAction(&req, requestID);
}
//�����ѯ��������û�����
TRADEAPI_API int ReqQueryCFMMCTradingAccountToken(CThostFtdcTraderApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
{
	if (pUserApi == NULL) return -1;

	CThostFtdcQueryCFMMCTradingAccountTokenField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.InvestorID, investorID);
	return pUserApi->ReqQueryCFMMCTradingAccountToken(&req, requestID);
}
//�ڻ����������ʽ�ת�ڻ�����
TRADEAPI_API int ReqFromBankToFutureByFuture(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcReqTransferField *reqTransfer)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqFromBankToFutureByFuture(reqTransfer, requestID);
}
//�ڻ������ڻ��ʽ�ת��������
TRADEAPI_API int ReqFromFutureToBankByFuture(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcReqTransferField *reqTransfer)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqFromFutureToBankByFuture(reqTransfer, requestID);
}
//�ڻ������ѯ�����������
TRADEAPI_API int ReqQueryBankAccountMoneyByFuture(CThostFtdcTraderApi* pUserApi, int requestID, CThostFtdcReqQueryAccountField *reqQueryAccount)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQueryBankAccountMoneyByFuture(reqQueryAccount, requestID);
}
#pragma endregion

#pragma region �ص�����
//========================================
//==================================== �ص����� =======================================

TRADEAPI_API void WINAPI RegOnFrontConnected(CTraderSpi* pUserSpi, CBOnFrontConnected cb)		//���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
{
	pUserSpi->cbOnFrontConnected = cb;
}

TRADEAPI_API void WINAPI RegOnFrontDisconnected(CTraderSpi* pUserSpi, CBOnFrontDisconnected cb)		//���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
{
	pUserSpi->cbOnFrontDisconnected = cb;
}

TRADEAPI_API void WINAPI RegOnHeartBeatWarning(CTraderSpi* pUserSpi, CBOnHeartBeatWarning cb)		//������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
{
	pUserSpi->cbOnHeartBeatWarning = cb;
}

TRADEAPI_API void WINAPI RegRspAuthenticate(CTraderSpi* pUserSpi, CBRspAuthenticate cb)
{
	pUserSpi->cbRspAuthenticate = cb;
}

TRADEAPI_API void WINAPI RegRspUserLogin(CTraderSpi* pUserSpi, CBRspUserLogin cb)	//��¼������Ӧ
{
	pUserSpi->cbRspUserLogin = cb;
}
TRADEAPI_API void WINAPI RegRspUserLogout(CTraderSpi* pUserSpi, CBRspUserLogout cb)	//�ǳ�������Ӧ
{
	pUserSpi->cbRspUserLogout = cb;
}
TRADEAPI_API void WINAPI RegRspUserPasswordUpdate(CTraderSpi* pUserSpi, CBRspUserPasswordUpdate cb)	//�û��������������Ӧ
{
	pUserSpi->cbRspUserPasswordUpdate = cb;
}
TRADEAPI_API void WINAPI RegRspTradingAccountPasswordUpdate(CTraderSpi* pUserSpi, CBRspTradingAccountPasswordUpdate cb)	//�ʽ��˻��������������Ӧ
{
	pUserSpi->cbRspTradingAccountPasswordUpdate = cb;
}
TRADEAPI_API void WINAPI RegRspOrderInsert(CTraderSpi* pUserSpi, CBRspOrderInsert cb)	//����¼��������Ӧ
{
	pUserSpi->cbRspOrderInsert = cb;
}
TRADEAPI_API void WINAPI RegRspParkedOrderInsert(CTraderSpi* pUserSpi, CBRspParkedOrderInsert cb)	//Ԥ��¼��������Ӧ
{
	pUserSpi->cbRspParkedOrderInsert = cb;
}
TRADEAPI_API void WINAPI RegRspParkedOrderAction(CTraderSpi* pUserSpi, CBRspParkedOrderAction cb)	//Ԥ�񳷵�¼��������Ӧ
{
	pUserSpi->cbRspParkedOrderAction = cb;
}
TRADEAPI_API void WINAPI RegRspOrderAction(CTraderSpi* pUserSpi, CBRspOrderAction cb)	//��������������Ӧ
{
	pUserSpi->cbRspOrderAction = cb;
}
TRADEAPI_API void WINAPI RegRspQueryMaxOrderVolume(CTraderSpi* pUserSpi, CBRspQueryMaxOrderVolume cb)	//��ѯ��󱨵�������Ӧ
{
	pUserSpi->cbRspQueryMaxOrderVolume = cb;
}
TRADEAPI_API void WINAPI RegRspSettlementInfoConfirm(CTraderSpi* pUserSpi, CBRspSettlementInfoConfirm cb)	//Ͷ���߽�����ȷ����Ӧ
{
	pUserSpi->cbRspSettlementInfoConfirm = cb;
}
TRADEAPI_API void WINAPI RegRspRemoveParkedOrder(CTraderSpi* pUserSpi, CBRspRemoveParkedOrder cb)	//ɾ��Ԥ����Ӧ
{
	pUserSpi->cbRspRemoveParkedOrder = cb;
}
TRADEAPI_API void WINAPI RegRspRemoveParkedOrderAction(CTraderSpi* pUserSpi, CBRspRemoveParkedOrderAction cb)	//ɾ��Ԥ�񳷵���Ӧ
{
	pUserSpi->cbRspRemoveParkedOrderAction = cb;
}
TRADEAPI_API void WINAPI RegBatchOrderAction(CTraderSpi* pUserSpi, CBRspBatchOrderAction cb)	//������������������Ӧ
{
	pUserSpi->cbRspBatchOrderAction = cb;
}
TRADEAPI_API void WINAPI RegCombActionInsert(CTraderSpi* pUserSpi, CBRspCombActionInsert cb)	//�������¼��������Ӧ
{
	pUserSpi->cbRspCombActionInsert = cb;
}
TRADEAPI_API void WINAPI RegRspQryOrder(CTraderSpi* pUserSpi, CBRspQryOrder cb)	//�����ѯ������Ӧ
{
	pUserSpi->cbRspQryOrder = cb;
}
TRADEAPI_API void WINAPI RegRspQryTrade(CTraderSpi* pUserSpi, CBRspQryTrade cb)	//�����ѯ�ɽ���Ӧ
{
	pUserSpi->cbRspQryTrade = cb;
}
TRADEAPI_API void WINAPI RegRspQryInvestorPosition(CTraderSpi* pUserSpi, CBRspQryInvestorPosition cb)	//�����ѯͶ���ֲ߳���Ӧ
{
	pUserSpi->cbRspQryInvestorPosition = cb;
}
TRADEAPI_API void WINAPI RegRspQryTradingAccount(CTraderSpi* pUserSpi, CBRspQryTradingAccount cb)	//�����ѯ�ʽ��˻���Ӧ
{
	pUserSpi->cbRspQryTradingAccount = cb;
}
TRADEAPI_API void WINAPI RegRspQryInvestor(CTraderSpi* pUserSpi, CBRspQryInvestor cb)	//�����ѯͶ������Ӧ
{
	pUserSpi->cbRspQryInvestor = cb;
}
TRADEAPI_API void WINAPI RegRspQryTradingCode(CTraderSpi* pUserSpi, CBRspQryTradingCode cb)	//�����ѯ���ױ�����Ӧ
{
	pUserSpi->cbRspQryTradingCode = cb;
}
TRADEAPI_API void WINAPI RegRspQryInstrumentMarginRate(CTraderSpi* pUserSpi, CBRspQryInstrumentMarginRate cb)	//�����ѯ��Լ��֤������Ӧ
{
	pUserSpi->cbRspQryInstrumentMarginRate = cb;
}
TRADEAPI_API void WINAPI RegRspQryInstrumentCommissionRate(CTraderSpi* pUserSpi, CBRspQryInstrumentCommissionRate cb)	//�����ѯ��Լ����������Ӧ
{
	pUserSpi->cbRspQryInstrumentCommissionRate = cb;
}
TRADEAPI_API void WINAPI RegRspQryExchange(CTraderSpi* pUserSpi, CBRspQryExchange cb)	//�����ѯ��������Ӧ
{
	pUserSpi->cbRspQryExchange = cb;
}
TRADEAPI_API void WINAPI RegRspQryInstrument(CTraderSpi* pUserSpi, CBRspQryInstrument cb)	//�����ѯ��Լ��Ӧ
{
	pUserSpi->cbRspQryInstrument = cb;
}
TRADEAPI_API void WINAPI RegRspQryDepthMarketData(CTraderSpi* pUserSpi, CBRspQryDepthMarketData cb)	//�����ѯ������Ӧ
{
	pUserSpi->cbRspQryDepthMarketData = cb;
}
TRADEAPI_API void WINAPI RegRspQrySettlementInfo(CTraderSpi* pUserSpi, CBRspQrySettlementInfo cb)	//�����ѯͶ���߽�������Ӧ
{
	pUserSpi->cbRspQrySettlementInfo = cb;
}
TRADEAPI_API void WINAPI RegRspQryTransferBank(CTraderSpi* pUserSpi, CBRspQryTransferBank cb)	//�����ѯת��������Ӧ
{
	pUserSpi->cbRspQryTransferBank = cb;
}
TRADEAPI_API void WINAPI RegRspQryInvestorPositionDetail(CTraderSpi* pUserSpi, CBRspQryInvestorPositionDetail cb)	//�����ѯͶ���ֲ߳���ϸ��Ӧ
{
	pUserSpi->cbRspQryInvestorPositionDetail = cb;
}
TRADEAPI_API void WINAPI RegRspQryNotice(CTraderSpi* pUserSpi, CBRspQryNotice cb)	//�����ѯ�ͻ�֪ͨ��Ӧ
{
	pUserSpi->cbRspQryNotice = cb;
}
TRADEAPI_API void WINAPI RegRspQrySettlementInfoConfirm(CTraderSpi* pUserSpi, CBRspQrySettlementInfoConfirm cb)	//�����ѯ������Ϣȷ����Ӧ
{
	pUserSpi->cbRspQrySettlementInfoConfirm = cb;
}
TRADEAPI_API void WINAPI RegRspQryInvestorPositionCombineDetail(CTraderSpi* pUserSpi, CBRspQryInvestorPositionCombineDetail cb)	//�����ѯͶ���ֲ߳���ϸ��Ӧ
{
	pUserSpi->cbRspQryInvestorPositionCombineDetail = cb;
}
TRADEAPI_API void WINAPI RegRspQryCFMMCTradingAccountKey(CTraderSpi* pUserSpi, CBRspQryCFMMCTradingAccountKey cb)	//��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ��Ӧ
{
	pUserSpi->cbRspQryCFMMCTradingAccountKey = cb;
}
TRADEAPI_API void WINAPI RegRspQryEWarrantOffset(CTraderSpi* pUserSpi, CBRspQryEWarrantOffset cb)	//�����ѯ�ֵ��۵���Ϣ
{
	pUserSpi->cbRspQryEWarrantOffset = cb;
}
TRADEAPI_API void WINAPI RegRspQryInvestorProductGroupMargin(CTraderSpi* pUserSpi, CBRspQryInvestorProductGroupMargin cb)	//�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
{
	pUserSpi->cbRspQryInvestorProductGroupMargin = cb;
}
TRADEAPI_API void WINAPI RegRspQryExchangeMarginRate(CTraderSpi* pUserSpi, CBRspQryExchangeMarginRate cb)	//�����ѯ��������֤����
{
	pUserSpi->cbRspQryExchangeMarginRate = cb;
}
TRADEAPI_API void WINAPI RegRspQryExchangeMarginRateAdjust(CTraderSpi* pUserSpi, CBRspQryExchangeMarginRateAdjust cb)	//�����ѯ������������֤����
{
	pUserSpi->cbRspQryExchangeMarginRateAdjust = cb;
}
TRADEAPI_API void WINAPI RegRspQryTransferSerial(CTraderSpi* pUserSpi, CBRspQryTransferSerial cb)	//�����ѯת����ˮ��Ӧ
{
	pUserSpi->cbRspQryTransferSerial = cb;
}
TRADEAPI_API void WINAPI RegRspQryAccountregister(CTraderSpi* pUserSpi, CBRspQryAccountregister cb)	//�����ѯ����ǩԼ��ϵ��Ӧ
{
	pUserSpi->cbRspQryAccountregister = cb;
}
TRADEAPI_API void WINAPI RegRspError(CTraderSpi* pUserSpi, CBRspError cb)	//����Ӧ��
{
	pUserSpi->cbRspError = cb;
}
TRADEAPI_API void WINAPI RegRtnOrder(CTraderSpi* pUserSpi, CBRtnOrder cb)	//����֪ͨ
{
	pUserSpi->cbRtnOrder = cb;
}
TRADEAPI_API void WINAPI RegRtnTrade(CTraderSpi* pUserSpi, CBRtnTrade cb)	//�ɽ�֪ͨ
{
	pUserSpi->cbRtnTrade = cb;
}
TRADEAPI_API void WINAPI RegErrRtnOrderInsert(CTraderSpi* pUserSpi, CBErrRtnOrderInsert cb)	//����¼�����ر�
{
	pUserSpi->cbErrRtnOrderInsert = cb;
}
TRADEAPI_API void WINAPI RegErrRtnOrderAction(CTraderSpi* pUserSpi, CBErrRtnOrderAction cb)	//������������ر�
{
	pUserSpi->cbErrRtnOrderAction = cb;
}
TRADEAPI_API void WINAPI RegRtnInstrumentStatus(CTraderSpi* pUserSpi, CBRtnInstrumentStatus cb)	//��Լ����״̬֪ͨ
{
	pUserSpi->cbRtnInstrumentStatus = cb;
}
TRADEAPI_API void WINAPI RegRtnTradingNotice(CTraderSpi* pUserSpi, CBRtnTradingNotice cb)	//����֪ͨ
{
	pUserSpi->cbRtnTradingNotice = cb;
}
TRADEAPI_API void WINAPI RegRtnErrorConditionalOrder(CTraderSpi* pUserSpi, CBRtnErrorConditionalOrder cb)	//��ʾ������У�����
{
	pUserSpi->cbRtnErrorConditionalOrder = cb;
}
TRADEAPI_API void WINAPI RegRspQryContractBank(CTraderSpi* pUserSpi, CBRspQryContractBank cb)	//�����ѯǩԼ������Ӧ
{
	pUserSpi->cbRspQryContractBank = cb;
}
TRADEAPI_API void WINAPI RegRspQryParkedOrder(CTraderSpi* pUserSpi, CBRspQryParkedOrder cb)	//�����ѯԤ����Ӧ
{
	pUserSpi->cbRspQryParkedOrder = cb;
}
TRADEAPI_API void WINAPI RegRspQryParkedOrderAction(CTraderSpi* pUserSpi, CBRspQryParkedOrderAction cb)	//�����ѯԤ�񳷵���Ӧ
{
	pUserSpi->cbRspQryParkedOrderAction = cb;
}
TRADEAPI_API void WINAPI RegRspQryTradingNotice(CTraderSpi* pUserSpi, CBRspQryTradingNotice cb)	//�����ѯ����֪ͨ��Ӧ
{
	pUserSpi->cbRspQryTradingNotice = cb;
}
TRADEAPI_API void WINAPI RegRspQryBrokerTradingParams(CTraderSpi* pUserSpi, CBRspQryBrokerTradingParams cb)	//�����ѯ���͹�˾���ײ�����Ӧ
{
	pUserSpi->cbRspQryBrokerTradingParams = cb;
}
TRADEAPI_API void WINAPI RegRspQryBrokerTradingAlgos(CTraderSpi* pUserSpi, CBRspQryBrokerTradingAlgos cb)	//�����ѯ���͹�˾�����㷨��Ӧ
{
	pUserSpi->cbRspQryBrokerTradingAlgos = cb;
}
TRADEAPI_API void WINAPI RegRtnFromBankToFutureByBank(CTraderSpi* pUserSpi, CBRtnFromBankToFutureByBank cb)	//���з��������ʽ�ת�ڻ�֪ͨ
{
	pUserSpi->cbRtnFromBankToFutureByBank = cb;
}
TRADEAPI_API void WINAPI RegRtnFromFutureToBankByBank(CTraderSpi* pUserSpi, CBRtnFromFutureToBankByBank cb)	//���з����ڻ��ʽ�ת����֪ͨ
{
	pUserSpi->cbRtnFromFutureToBankByBank = cb;
}
TRADEAPI_API void WINAPI RegRtnRepealFromBankToFutureByBank(CTraderSpi* pUserSpi, CBRtnRepealFromBankToFutureByBank cb)	//���з����������ת�ڻ�֪ͨ
{
	pUserSpi->cbRtnRepealFromBankToFutureByBank = cb;
}
TRADEAPI_API void WINAPI RegRtnRepealFromFutureToBankByBank(CTraderSpi* pUserSpi, CBRtnRepealFromFutureToBankByBank cb)	//���з�������ڻ�ת����֪ͨ
{
	pUserSpi->cbRtnRepealFromFutureToBankByBank = cb;
}
TRADEAPI_API void WINAPI RegRtnFromBankToFutureByFuture(CTraderSpi* pUserSpi, CBRtnFromBankToFutureByFuture cb)	//�ڻ����������ʽ�ת�ڻ�֪ͨ
{
	pUserSpi->cbRtnFromBankToFutureByFuture = cb;
}
TRADEAPI_API void WINAPI RegRtnFromFutureToBankByFuture(CTraderSpi* pUserSpi, CBRtnFromFutureToBankByFuture cb)	//�ڻ������ڻ��ʽ�ת����֪ͨ
{
	pUserSpi->cbRtnFromFutureToBankByFuture = cb;
}
TRADEAPI_API void WINAPI RegRtnRepealFromBankToFutureByFutureManual(CTraderSpi* pUserSpi, CBRtnRepealFromBankToFutureByFutureManual cb)	//ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
{
	pUserSpi->cbRtnRepealFromBankToFutureByFutureManual = cb;
}
TRADEAPI_API void WINAPI RegRtnRepealFromFutureToBankByFutureManual(CTraderSpi* pUserSpi, CBRtnRepealFromFutureToBankByFutureManual cb)	//ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
{
	pUserSpi->cbRtnRepealFromFutureToBankByFutureManual = cb;
}
TRADEAPI_API void WINAPI RegRtnQueryBankBalanceByFuture(CTraderSpi* pUserSpi, CBRtnQueryBankBalanceByFuture cb)	//�ڻ������ѯ�������֪ͨ
{
	pUserSpi->cbRtnQueryBankBalanceByFuture = cb;
}
TRADEAPI_API void WINAPI RegErrRtnBankToFutureByFuture(CTraderSpi* pUserSpi, CBErrRtnBankToFutureByFuture cb)	//�ڻ����������ʽ�ת�ڻ�����ر�
{
	pUserSpi->cbErrRtnBankToFutureByFuture = cb;
}
TRADEAPI_API void WINAPI RegErrRtnFutureToBankByFuture(CTraderSpi* pUserSpi, CBErrRtnFutureToBankByFuture cb)	//�ڻ������ڻ��ʽ�ת���д���ر�
{
	pUserSpi->cbErrRtnFutureToBankByFuture = cb;
}
TRADEAPI_API void WINAPI RegErrRtnRepealBankToFutureByFutureManual(CTraderSpi* pUserSpi, CBErrRtnRepealBankToFutureByFutureManual cb)	//ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ�����ر�
{
	pUserSpi->cbErrRtnRepealBankToFutureByFutureManual = cb;
}
TRADEAPI_API void WINAPI RegErrRtnRepealFutureToBankByFutureManual(CTraderSpi* pUserSpi, CBErrRtnRepealFutureToBankByFutureManual cb)	//ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת���д���ر�
{
	pUserSpi->cbErrRtnRepealFutureToBankByFutureManual = cb;
}
TRADEAPI_API void WINAPI RegErrRtnQueryBankBalanceByFuture(CTraderSpi* pUserSpi, CBErrRtnQueryBankBalanceByFuture cb)	//�ڻ������ѯ����������ر�
{
	pUserSpi->cbErrRtnQueryBankBalanceByFuture = cb;
}
TRADEAPI_API void WINAPI RegRtnRepealFromBankToFutureByFuture(CTraderSpi* pUserSpi, CBRtnRepealFromBankToFutureByFuture cb)	//�ڻ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
{
	pUserSpi->cbRtnRepealFromBankToFutureByFuture = cb;
}
TRADEAPI_API void WINAPI RegRtnRepealFromFutureToBankByFuture(CTraderSpi* pUserSpi, CBRtnRepealFromFutureToBankByFuture cb)	//�ڻ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
{
	pUserSpi->cbRtnRepealFromFutureToBankByFuture = cb;
}
TRADEAPI_API void WINAPI RegRspFromBankToFutureByFuture(CTraderSpi* pUserSpi, CBRspFromBankToFutureByFuture cb)	//�ڻ����������ʽ�ת�ڻ�Ӧ��
{
	pUserSpi->cbRspFromBankToFutureByFuture = cb;
}
TRADEAPI_API void WINAPI RegRspFromFutureToBankByFuture(CTraderSpi* pUserSpi, CBRspFromFutureToBankByFuture cb)	//�ڻ������ڻ��ʽ�ת����Ӧ��
{
	pUserSpi->cbRspFromFutureToBankByFuture = cb;
}
TRADEAPI_API void WINAPI RegRspQueryBankAccountMoneyByFuture(CTraderSpi* pUserSpi, CBRspQueryBankAccountMoneyByFuture cb)	//�ڻ������ѯ�������Ӧ��
{
	pUserSpi->cbRspQueryBankAccountMoneyByFuture = cb;
}
#pragma endregion