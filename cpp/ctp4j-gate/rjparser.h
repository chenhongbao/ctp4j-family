#pragma once
#include "rjmacro.h"
#include "ThostFtdcUserApiStruct.h"

setter_def(CThostFtdcDepthMarketDataField) {
    parse_or_throw();
    set_string(TradingDay);
    set_string(InstrumentID);
    set_string(ExchangeID);
    set_string(ExchangeInstID);
    set_double(LastPrice);
    set_double(PreSettlementPrice);
    set_double(PreClosePrice);
    set_double(PreOpenInterest);
    set_double(OpenPrice);
    set_double(HighestPrice);
    set_double(LowestPrice);
    set_int(Volume);
    set_double(Turnover);
    set_double(OpenInterest);
    set_double(ClosePrice);
    set_double(SettlementPrice);
    set_double(UpperLimitPrice);
    set_double(LowerLimitPrice);
    set_double(PreDelta);
    set_double(CurrDelta);
    set_string(UpdateTime);
    set_int(UpdateMillisec);
    set_double(BidPrice1);
    set_int(BidVolume1);
    set_double(AskPrice1);
    set_int(AskVolume1);
    set_double(BidPrice2);
    set_int(BidVolume2);
    set_double(AskPrice2);
    set_int(AskVolume2);
    set_double(BidPrice3);
    set_int(BidVolume3);
    set_double(AskPrice3);
    set_int(AskVolume3);
    set_double(BidPrice4);
    set_int(BidVolume4);
    set_double(AskPrice4);
    set_int(AskVolume4);
    set_double(BidPrice5);
    set_int(BidVolume5);
    set_double(AskPrice5);
    set_int(AskVolume5);
    set_double(AveragePrice);
    set_string(ActionDay);
}
getter_def(CThostFtdcDepthMarketDataField) {
    document();
    get_string(TradingDay);
    get_string(InstrumentID);
    get_string(ExchangeID);
    get_string(ExchangeInstID);
    get_double(LastPrice);
    get_double(PreSettlementPrice);
    get_double(PreClosePrice);
    get_double(PreOpenInterest);
    get_double(OpenPrice);
    get_double(HighestPrice);
    get_double(LowestPrice);
    get_int(Volume);
    get_double(Turnover);
    get_double(OpenInterest);
    get_double(ClosePrice);
    get_double(SettlementPrice);
    get_double(UpperLimitPrice);
    get_double(LowerLimitPrice);
    get_double(PreDelta);
    get_double(CurrDelta);
    get_string(UpdateTime);
    get_int(UpdateMillisec);
    get_double(BidPrice1);
    get_int(BidVolume1);
    get_double(AskPrice1);
    get_int(AskVolume1);
    get_double(BidPrice2);
    get_int(BidVolume2);
    get_double(AskPrice2);
    get_int(AskVolume2);
    get_double(BidPrice3);
    get_int(BidVolume3);
    get_double(AskPrice3);
    get_int(AskVolume3);
    get_double(BidPrice4);
    get_int(BidVolume4);
    get_double(AskPrice4);
    get_int(AskVolume4);
    get_double(BidPrice5);
    get_int(BidVolume5);
    get_double(AskPrice5);
    get_int(AskVolume5);
    get_double(AveragePrice);
    get_string(ActionDay);
    write_document();
}

setter_def(CThostFtdcInputOrderActionField) {
    parse_or_throw();
    set_string(BrokerID);
    set_string(InvestorID);
    set_int(OrderActionRef);
    set_string(OrderRef);
    set_int(RequestID);
    set_int(FrontID);
    set_int(SessionID);
    set_string(ExchangeID);
    set_string(OrderSysID);
    set_flag(ActionFlag, ActionFlag);
    set_double(LimitPrice);
    set_int(VolumeChange);
    set_string(UserID);
    set_string(InstrumentID);
    set_string(InvestUnitID);
    set_string(IPAddress);
    set_string(MacAddress);
}
getter_def(CThostFtdcInputOrderActionField) {
    document();
    get_string(BrokerID);
    get_string(InvestorID);
    get_int(OrderActionRef);
    get_string(OrderRef);
    get_int(RequestID);
    get_int(FrontID);
    get_int(SessionID);
    get_string(ExchangeID);
    get_string(OrderSysID);
    get_flag(ActionFlag, ActionFlag);
    get_double(LimitPrice);
    get_int(VolumeChange);
    get_string(UserID);
    get_string(InstrumentID);
    get_string(InvestUnitID);
    get_string(IPAddress);
    get_string(MacAddress);
    write_document();
}
setter_def(CThostFtdcInputOrderField) {
    parse_or_throw();
    set_string(BrokerID);
    set_string(InvestorID);
    set_string(InstrumentID);
    set_string(OrderRef);
    set_string(UserID);
    set_flag(OrderPriceType, OrderPriceType);
    set_flag(Direction, Direction);
    set_flag(CombOffsetFlag[0], CombOffsetFlag);
    set_flag(CombHedgeFlag[0], CombHedgeFlag);
    set_double(LimitPrice);
    set_int(VolumeTotalOriginal);
    set_flag(TimeCondition, TimeCondition);
    set_string(GTDDate);
    set_flag(VolumeCondition, VolumeCondition);
    set_int(MinVolume);
    set_flag(ContingentCondition, ContingentCondition);
    set_double(StopPrice);
    set_flag(ForceCloseReason, ForceCloseReason);
    set_int(IsAutoSuspend);
    set_string(BusinessUnit);
    set_int(RequestID);
    set_int(UserForceClose);
    set_int(IsSwapOrder);
    set_string(ExchangeID);
    set_string(InvestUnitID);
    set_string(AccountID);
    set_string(CurrencyID);
    set_string(ClientID);
    set_string(IPAddress);
    set_string(MacAddress);
}
getter_def(CThostFtdcInputOrderField) {
    document();
    get_string(BrokerID);
    get_string(InvestorID);
    get_string(InstrumentID);
    get_string(OrderRef);
    get_string(UserID);
    get_flag(OrderPriceType, OrderPriceType);
    get_flag(Direction, Direction);
    get_flag(CombOffsetFlag[0], CombOffsetFlag);
    get_flag(CombHedgeFlag[0], CombHedgeFlag);
    get_double(LimitPrice);
    get_int(VolumeTotalOriginal);
    get_flag(TimeCondition, TimeCondition);
    get_string(GTDDate);
    get_flag(VolumeCondition, VolumeCondition);
    get_int(MinVolume);
    get_flag(ContingentCondition, ContingentCondition);
    get_double(StopPrice);
    get_flag(ForceCloseReason, ForceCloseReason);
    get_int(IsAutoSuspend);
    get_string(BusinessUnit);
    get_int(RequestID);
    get_int(UserForceClose);
    get_int(IsSwapOrder);
    get_string(ExchangeID);
    get_string(InvestUnitID);
    get_string(AccountID);
    get_string(CurrencyID);
    get_string(ClientID);
    get_string(IPAddress);
    get_string(MacAddress);
    write_document();
}
setter_def(CThostFtdcInstrumentCommissionRateField) {
    parse_or_throw();
    set_string(InstrumentID);
    set_flag(InvestorRange, InvestorRange);
    set_string(BrokerID);
    set_string(InvestorID);
    set_double(OpenRatioByMoney);
    set_double(OpenRatioByVolume);
    set_double(CloseRatioByMoney);
    set_double(CloseRatioByVolume);
    set_double(CloseTodayRatioByMoney);
    set_double(CloseTodayRatioByVolume);
    set_string(ExchangeID);
    set_flag(BizType, BizType);
    set_string(InvestUnitID);
}
getter_def(CThostFtdcInstrumentCommissionRateField) {
    document();
    get_string(InstrumentID);
    get_flag(InvestorRange, InvestorRange);
    get_string(BrokerID);
    get_string(InvestorID);
    get_double(OpenRatioByMoney);
    get_double(OpenRatioByVolume);
    get_double(CloseRatioByMoney);
    get_double(CloseRatioByVolume);
    get_double(CloseTodayRatioByMoney);
    get_double(CloseTodayRatioByVolume);
    get_string(ExchangeID);
    get_flag(BizType, BizType);
    get_string(InvestUnitID);
    write_document();
}
setter_def(CThostFtdcInstrumentField) {
    parse_or_throw();
    set_string(InstrumentID);
    set_string(ExchangeID);
    set_string(InstrumentName);
    set_string(ExchangeInstID);
    set_string(ProductID);
    set_flag(ProductClass, ProductClass);
    set_int(DeliveryYear);
    set_int(DeliveryMonth);
    set_int(MaxMarketOrderVolume);
    set_int(MinMarketOrderVolume);
    set_int(MaxLimitOrderVolume);
    set_int(MinLimitOrderVolume);
    set_int(VolumeMultiple);
    set_double(PriceTick);
    set_string(CreateDate);
    set_string(OpenDate);
    set_string(ExpireDate);
    set_string(StartDelivDate);
    set_string(EndDelivDate);
    set_flag(InstLifePhase, InstLifePhase);
    set_int(IsTrading);
    set_flag(PositionType, PositionType);
    set_flag(PositionDateType, PositionDateType);
    set_double(LongMarginRatio);
    set_double(ShortMarginRatio);
    set_flag(MaxMarginSideAlgorithm, MaxMarginSideAlgorithm);
    set_string(UnderlyingInstrID);
    set_double(StrikePrice);
    set_flag(OptionsType, OptionsType);
    set_double(UnderlyingMultiple);
    set_flag(CombinationType, CombinationType);
}
getter_def(CThostFtdcInstrumentField) {
    document();
    get_string(InstrumentID);
    get_string(ExchangeID);
    get_string(InstrumentName);
    get_string(ExchangeInstID);
    get_string(ProductID);
    get_flag(ProductClass, ProductClass);
    get_int(DeliveryYear);
    get_int(DeliveryMonth);
    get_int(MaxMarketOrderVolume);
    get_int(MinMarketOrderVolume);
    get_int(MaxLimitOrderVolume);
    get_int(MinLimitOrderVolume);
    get_int(VolumeMultiple);
    get_double(PriceTick);
    get_string(CreateDate);
    get_string(OpenDate);
    get_string(ExpireDate);
    get_string(StartDelivDate);
    get_string(EndDelivDate);
    get_flag(InstLifePhase, InstLifePhase);
    get_int(IsTrading);
    get_flag(PositionType, PositionType);
    get_flag(PositionDateType, PositionDateType);
    get_double(LongMarginRatio);
    get_double(ShortMarginRatio);
    get_flag(MaxMarginSideAlgorithm, MaxMarginSideAlgorithm);
    get_string(UnderlyingInstrID);
    get_double(StrikePrice);
    get_flag(OptionsType, OptionsType);
    get_double(UnderlyingMultiple);
    get_flag(CombinationType, CombinationType);
    write_document();
}
setter_def(CThostFtdcInstrumentMarginRateField) {
    parse_or_throw();
    set_string(InstrumentID);
    set_flag(InvestorRange, InvestorRange);
    set_string(BrokerID);
    set_string(InvestorID);
    set_flag(HedgeFlag, HedgeFlag);
    set_double(LongMarginRatioByMoney);
    set_double(LongMarginRatioByVolume);
    set_double(ShortMarginRatioByMoney);
    set_double(ShortMarginRatioByVolume);
    set_int(IsRelative);
    set_string(ExchangeID);
    set_string(InvestUnitID);
}
getter_def(CThostFtdcInstrumentMarginRateField) {
    document();
    get_string(InstrumentID);
    get_flag(InvestorRange, InvestorRange);
    get_string(BrokerID);
    get_string(InvestorID);
    get_flag(HedgeFlag, HedgeFlag);
    get_double(LongMarginRatioByMoney);
    get_double(LongMarginRatioByVolume);
    get_double(ShortMarginRatioByMoney);
    get_double(ShortMarginRatioByVolume);
    get_int(IsRelative);
    get_string(ExchangeID);
    get_string(InvestUnitID);
    write_document();
}
setter_def(CThostFtdcInvestorPositionDetailField) {
    parse_or_throw();
    set_string(InstrumentID);
    set_string(BrokerID);
    set_string(InvestorID);
    set_flag(HedgeFlag, HedgeFlag);
    set_flag(Direction, Direction);
    set_string(OpenDate);
    set_string(TradeID);
    set_int(Volume);
    set_double(OpenPrice);
    set_string(TradingDay);
    set_int(SettlementID);
    set_flag(TradeType, TradeType);
    set_string(CombInstrumentID);
    set_string(ExchangeID);
    set_double(CloseProfitByDate);
    set_double(CloseProfitByTrade);
    set_double(PositionProfitByDate);
    set_double(PositionProfitByTrade);
    set_double(Margin);
    set_double(ExchMargin);
    set_double(MarginRateByMoney);
    set_double(MarginRateByVolume);
    set_double(LastSettlementPrice);
    set_double(SettlementPrice);
    set_int(CloseVolume);
    set_double(CloseAmount);
    set_int(TimeFirstVolume);
    set_string(InvestUnitID);
}
getter_def(CThostFtdcInvestorPositionDetailField) {
    document();
    get_string(InstrumentID);
    get_string(BrokerID);
    get_string(InvestorID);
    get_flag(HedgeFlag, HedgeFlag);
    get_flag(Direction, Direction);
    get_string(OpenDate);
    get_string(TradeID);
    get_int(Volume);
    get_double(OpenPrice);
    get_string(TradingDay);
    get_int(SettlementID);
    get_flag(TradeType, TradeType);
    get_string(CombInstrumentID);
    get_string(ExchangeID);
    get_double(CloseProfitByDate);
    get_double(CloseProfitByTrade);
    get_double(PositionProfitByDate);
    get_double(PositionProfitByTrade);
    get_double(Margin);
    get_double(ExchMargin);
    get_double(MarginRateByMoney);
    get_double(MarginRateByVolume);
    get_double(LastSettlementPrice);
    get_double(SettlementPrice);
    get_int(CloseVolume);
    get_double(CloseAmount);
    get_int(TimeFirstVolume);
    get_string(InvestUnitID);
    write_document();
}
setter_def(CThostFtdcInvestorPositionField) {
    parse_or_throw();
    set_string(InstrumentID);
    set_string(BrokerID);
    set_string(InvestorID);
    set_flag(PosiDirection, PosiDirection);
    set_flag(HedgeFlag, HedgeFlag);
    set_flag(PositionDate, PositionDate);
    set_int(YdPosition);
    set_int(Position);
    set_int(LongFrozen);
    set_int(ShortFrozen);
    set_double(LongFrozenAmount);
    set_double(ShortFrozenAmount);
    set_int(OpenVolume);
    set_int(CloseVolume);
    set_double(OpenAmount);
    set_double(CloseAmount);
    set_double(PositionCost);
    set_double(PreMargin);
    set_double(UseMargin);
    set_double(FrozenMargin);
    set_double(FrozenCash);
    set_double(FrozenCommission);
    set_double(CashIn);
    set_double(Commission);
    set_double(CloseProfit);
    set_double(PositionProfit);
    set_double(PreSettlementPrice);
    set_double(SettlementPrice);
    set_string(TradingDay);
    set_int(SettlementID);
    set_double(OpenCost);
    set_double(ExchangeMargin);
    set_int(CombPosition);
    set_int(CombLongFrozen);
    set_int(CombShortFrozen);
    set_double(CloseProfitByDate);
    set_double(CloseProfitByTrade);
    set_int(TodayPosition);
    set_double(MarginRateByMoney);
    set_double(MarginRateByVolume);
    set_int(StrikeFrozen);
    set_double(StrikeFrozenAmount);
    set_int(AbandonFrozen);
    set_string(ExchangeID);
    set_int(YdStrikeFrozen);
    set_string(InvestUnitID);
    set_double(PositionCostOffset);
}
getter_def(CThostFtdcInvestorPositionField) {
    document();
    get_string(InstrumentID);
    get_string(BrokerID);
    get_string(InvestorID);
    get_flag(PosiDirection, PosiDirection);
    get_flag(HedgeFlag, HedgeFlag);
    get_flag(PositionDate, PositionDate);
    get_int(YdPosition);
    get_int(Position);
    get_int(LongFrozen);
    get_int(ShortFrozen);
    get_double(LongFrozenAmount);
    get_double(ShortFrozenAmount);
    get_int(OpenVolume);
    get_int(CloseVolume);
    get_double(OpenAmount);
    get_double(CloseAmount);
    get_double(PositionCost);
    get_double(PreMargin);
    get_double(UseMargin);
    get_double(FrozenMargin);
    get_double(FrozenCash);
    get_double(FrozenCommission);
    get_double(CashIn);
    get_double(Commission);
    get_double(CloseProfit);
    get_double(PositionProfit);
    get_double(PreSettlementPrice);
    get_double(SettlementPrice);
    get_string(TradingDay);
    get_int(SettlementID);
    get_double(OpenCost);
    get_double(ExchangeMargin);
    get_int(CombPosition);
    get_int(CombLongFrozen);
    get_int(CombShortFrozen);
    get_double(CloseProfitByDate);
    get_double(CloseProfitByTrade);
    get_int(TodayPosition);
    get_double(MarginRateByMoney);
    get_double(MarginRateByVolume);
    get_int(StrikeFrozen);
    get_double(StrikeFrozenAmount);
    get_int(AbandonFrozen);
    get_string(ExchangeID);
    get_int(YdStrikeFrozen);
    get_string(InvestUnitID);
    get_double(PositionCostOffset);
    write_document();
}
setter_def(CThostFtdcOrderActionField) {
    parse_or_throw();
    set_string(BrokerID);
    set_string(InvestorID);
    set_int(OrderActionRef);
    set_string(OrderRef);
    set_int(RequestID);
    set_int(FrontID);
    set_int(SessionID);
    set_string(ExchangeID);
    set_string(OrderSysID);
    set_flag(ActionFlag, ActionFlag);
    set_double(LimitPrice);
    set_int(VolumeChange);
    set_string(ActionDate);
    set_string(ActionTime);
    set_string(TraderID);
    set_int(InstallID);
    set_string(OrderLocalID);
    set_string(ActionLocalID);
    set_string(ParticipantID);
    set_string(ClientID);
    set_string(BusinessUnit);
    set_flag(OrderActionStatus, OrderActionStatus);
    set_string(UserID);
    set_string(StatusMsg);
    set_string(InstrumentID);
    set_string(BranchID);
    set_string(InvestUnitID);
    set_string(IPAddress);
    set_string(MacAddress);
}
getter_def(CThostFtdcOrderActionField) {
    document();
    get_string(BrokerID);
    get_string(InvestorID);
    get_int(OrderActionRef);
    get_string(OrderRef);
    get_int(RequestID);
    get_int(FrontID);
    get_int(SessionID);
    get_string(ExchangeID);
    get_string(OrderSysID);
    get_flag(ActionFlag, ActionFlag);
    get_double(LimitPrice);
    get_int(VolumeChange);
    get_string(ActionDate);
    get_string(ActionTime);
    get_string(TraderID);
    get_int(InstallID);
    get_string(OrderLocalID);
    get_string(ActionLocalID);
    get_string(ParticipantID);
    get_string(ClientID);
    get_string(BusinessUnit);
    get_flag(OrderActionStatus, OrderActionStatus);
    get_string(UserID);
    get_string(StatusMsg);
    get_string(InstrumentID);
    get_string(BranchID);
    get_string(InvestUnitID);
    get_string(IPAddress);
    get_string(MacAddress);
    write_document();
}
setter_def(CThostFtdcOrderField) {
    parse_or_throw();
    set_string(BrokerID);
    set_string(InvestorID);
    set_string(InstrumentID);
    set_string(OrderRef);
    set_string(UserID);
    set_flag(OrderPriceType, OrderPriceType);
    set_flag(Direction, Direction);
    set_flag(CombOffsetFlag[0], CombOffsetFlag);
    set_flag(CombHedgeFlag[0], CombHedgeFlag);
    set_double(LimitPrice);
    set_int(VolumeTotalOriginal);
    set_flag(TimeCondition, TimeCondition);
    set_string(GTDDate);
    set_flag(VolumeCondition, VolumeCondition);
    set_int(MinVolume);
    set_flag(ContingentCondition, ContingentCondition);
    set_double(StopPrice);
    set_flag(ForceCloseReason, ForceCloseReason);
    set_int(IsAutoSuspend);
    set_string(BusinessUnit);
    set_int(RequestID);
    set_string(OrderLocalID);
    set_string(ExchangeID);
    set_string(ParticipantID);
    set_string(ClientID);
    set_string(ExchangeInstID);
    set_string(TraderID);
    set_int(InstallID);
    set_flag(OrderSubmitStatus, OrderSubmitStatus);
    set_int(NotifySequence);
    set_string(TradingDay);
    set_int(SettlementID);
    set_string(OrderSysID);
    set_flag(OrderSource, OrderSource);
    set_flag(OrderStatus, OrderStatus);
    set_flag(OrderType, OrderType);
    set_int(VolumeTraded);
    set_int(VolumeTotal);
    set_string(InsertDate);
    set_string(InsertTime);
    set_string(ActiveTime);
    set_string(SuspendTime);
    set_string(UpdateTime);
    set_string(CancelTime);
    set_string(ActiveTraderID);
    set_string(ClearingPartID);
    set_int(SequenceNo);
    set_int(FrontID);
    set_int(SessionID);
    set_string(UserProductInfo);
    set_string(StatusMsg);
    set_int(UserForceClose);
    set_string(ActiveUserID);
    set_int(BrokerOrderSeq);
    set_string(RelativeOrderSysID);
    set_int(ZCETotalTradedVolume);
    set_int(IsSwapOrder);
    set_string(BranchID);
    set_string(InvestUnitID);
    set_string(AccountID);
    set_string(CurrencyID);
    set_string(IPAddress);
    set_string(MacAddress);
}
getter_def(CThostFtdcOrderField) {
    document();
    get_string(BrokerID);
    get_string(InvestorID);
    get_string(InstrumentID);
    get_string(OrderRef);
    get_string(UserID);
    get_flag(OrderPriceType, OrderPriceType);
    get_flag(Direction, Direction);
    get_flag(CombOffsetFlag[0], CombOffsetFlag);
    get_flag(CombHedgeFlag[0], CombHedgeFlag);
    get_double(LimitPrice);
    get_int(VolumeTotalOriginal);
    get_flag(TimeCondition, TimeCondition);
    get_string(GTDDate);
    get_flag(VolumeCondition, VolumeCondition);
    get_int(MinVolume);
    get_flag(ContingentCondition, ContingentCondition);
    get_double(StopPrice);
    get_flag(ForceCloseReason, ForceCloseReason);
    get_int(IsAutoSuspend);
    get_string(BusinessUnit);
    get_int(RequestID);
    get_string(OrderLocalID);
    get_string(ExchangeID);
    get_string(ParticipantID);
    get_string(ClientID);
    get_string(ExchangeInstID);
    get_string(TraderID);
    get_int(InstallID);
    get_flag(OrderSubmitStatus, OrderSubmitStatus);
    get_int(NotifySequence);
    get_string(TradingDay);
    get_int(SettlementID);
    get_string(OrderSysID);
    get_flag(OrderSource, OrderSource);
    get_flag(OrderStatus, OrderStatus);
    get_flag(OrderType, get_flag);
    get_int(VolumeTraded);
    get_int(VolumeTotal);
    get_string(InsertDate);
    get_string(InsertTime);
    get_string(ActiveTime);
    get_string(SuspendTime);
    get_string(UpdateTime);
    get_string(CancelTime);
    get_string(ActiveTraderID);
    get_string(ClearingPartID);
    get_int(SequenceNo);
    get_int(FrontID);
    get_int(SessionID);
    get_string(UserProductInfo);
    get_string(StatusMsg);
    get_int(UserForceClose);
    get_string(ActiveUserID);
    get_int(BrokerOrderSeq);
    get_string(RelativeOrderSysID);
    get_int(ZCETotalTradedVolume);
    get_int(IsSwapOrder);
    get_string(BranchID);
    get_string(InvestUnitID);
    get_string(AccountID);
    get_string(CurrencyID);
    get_string(IPAddress);
    get_string(MacAddress);
    write_document();
}

setter_def(CThostFtdcQryInstrumentCommissionRateField) {
    parse_or_throw();
    set_string(BrokerID);
    set_string(InvestorID);
    set_string(InstrumentID);
    set_string(ExchangeID);
    set_string(InvestUnitID);
}
getter_def(CThostFtdcQryInstrumentCommissionRateField) {
    document();
    get_string(BrokerID);
    get_string(InvestorID);
    get_string(InstrumentID);
    get_string(ExchangeID);
    get_string(InvestUnitID);
    write_document();
}
setter_def(CThostFtdcQryInstrumentField) {
    parse_or_throw();
    set_string(InstrumentID);
    set_string(ExchangeID);
    set_string(ExchangeInstID);
    set_string(ProductID);
}
getter_def(CThostFtdcQryInstrumentField) {
    document();
    get_string(InstrumentID);
    get_string(ExchangeID);
    get_string(ExchangeInstID);
    get_string(ProductID);
    write_document();
}
setter_def(CThostFtdcQryInstrumentMarginRateField) {
    parse_or_throw();
    set_string(BrokerID);
    set_string(InvestorID);
    set_string(InstrumentID);
    set_flag(HedgeFlag, HedgeFlag);
    set_string(ExchangeID);
    set_string(InvestUnitID);
}
getter_def(CThostFtdcQryInstrumentMarginRateField) {
    document();
    get_string(BrokerID);
    get_string(InvestorID);
    get_string(InstrumentID);
    get_flag(HedgeFlag, HedgeFlag);
    get_string(ExchangeID);
    get_string(InvestUnitID);
    write_document();
}
setter_def(CThostFtdcQryInvestorPositionDetailField) {
    parse_or_throw();
    set_string(BrokerID);
    set_string(InvestorID);
    set_string(InstrumentID);
    set_string(ExchangeID);
    set_string(InvestUnitID);
}
getter_def(CThostFtdcQryInvestorPositionDetailField) {
    document();
    get_string(BrokerID);
    get_string(InvestorID);
    get_string(InstrumentID);
    get_string(ExchangeID);
    get_string(InvestUnitID);
    write_document();
}
setter_def(CThostFtdcQryInvestorPositionField) {
    parse_or_throw();
    set_string(BrokerID);
    set_string(InvestorID);
    set_string(InstrumentID);
    set_string(ExchangeID);
    set_string(InvestUnitID);
}
getter_def(CThostFtdcQryInvestorPositionField) {
    document();
    get_string(BrokerID);
    get_string(InvestorID);
    get_string(InstrumentID);
    get_string(ExchangeID);
    get_string(InvestUnitID);
    write_document();
}
setter_def(CThostFtdcQryTradingAccountField) {
    parse_or_throw();
    set_string(BrokerID);
    set_string(InvestorID);
    set_string(CurrencyID);
    set_flag(BizType, BizType);
    set_string(AccountID);
}
getter_def(CThostFtdcQryTradingAccountField) {
    document();
    get_string(BrokerID);
    get_string(InvestorID);
    get_string(CurrencyID);
    get_flag(BizType, BizType);
    get_string(AccountID);
    write_document();
}
setter_def(CThostFtdcReqAuthenticateField) {
    parse_or_throw();
    set_string(BrokerID);
    set_string(UserID);
    set_string(UserProductInfo);
    set_string(AuthCode);
    set_string(AppID);
}
getter_def(CThostFtdcReqAuthenticateField) {
    document();
    get_string(BrokerID);
    get_string(UserID);
    get_string(UserProductInfo);
    get_string(AuthCode);
    get_string(AppID);
    write_document();
}
setter_def(CThostFtdcReqUserLoginField) {
    parse_or_throw();
    set_string(TradingDay);
    set_string(BrokerID);
    set_string(UserID);
    set_string(Password);
    set_string(UserProductInfo);
    set_string(InterfaceProductInfo);
    set_string(ProtocolInfo);
    set_string(MacAddress);
    set_string(OneTimePassword);
    set_string(ClientIPAddress);
    set_string(LoginRemark);
    set_int(ClientIPPort);
}
getter_def(CThostFtdcReqUserLoginField) {
    document();
    get_string(TradingDay);
    get_string(BrokerID);
    get_string(UserID);
    get_string(Password);
    get_string(UserProductInfo);
    get_string(InterfaceProductInfo);
    get_string(ProtocolInfo);
    get_string(MacAddress);
    get_string(OneTimePassword);
    get_string(ClientIPAddress);
    get_string(LoginRemark);
    get_int(ClientIPPort);
    write_document();
}
setter_def(CThostFtdcRspAuthenticateField) {
    parse_or_throw();
    set_string(BrokerID);
    set_string(UserID);
    set_string(UserProductInfo);
    set_string(AppID);
    set_flag(AppType, AppType);
}
getter_def(CThostFtdcRspAuthenticateField) {
    document();
    get_string(BrokerID);
    get_string(UserID);
    get_string(UserProductInfo);
    get_string(AppID);
    get_flag(AppType, AppType);
    write_document();
}
setter_def(CThostFtdcRspInfoField) {
    parse_or_throw();
    set_int(ErrorID);
    set_string(ErrorMsg);
}
getter_def(CThostFtdcRspInfoField) {
    document();
    get_int(ErrorID);
    get_string(ErrorMsg);
    write_document();
}
setter_def(CThostFtdcRspUserLoginField) {
    parse_or_throw();
    set_string(TradingDay);
    set_string(LoginTime);
    set_string(BrokerID);
    set_string(UserID);
    set_string(SystemName);
    set_int(FrontID);
    set_int(SessionID);
    set_string(MaxOrderRef);
    set_string(SHFETime);
    set_string(DCETime);
    set_string(CZCETime);
    set_string(FFEXTime);
    set_string(INETime);
}
getter_def(CThostFtdcRspUserLoginField) {
    document();
    get_string(TradingDay);
    get_string(LoginTime);
    get_string(BrokerID);
    get_string(UserID);
    get_string(SystemName);
    get_int(FrontID);
    get_int(SessionID);
    get_string(MaxOrderRef);
    get_string(SHFETime);
    get_string(DCETime);
    get_string(CZCETime);
    get_string(FFEXTime);
    get_string(INETime);
    write_document();
}
setter_def(CThostFtdcSettlementInfoConfirmField) {
    parse_or_throw();
    set_string(BrokerID);
    set_string(InvestorID);
    set_string(ConfirmDate);
    set_string(ConfirmTime);
    set_int(SettlementID);
    set_string(AccountID);
    set_string(CurrencyID);
}
getter_def(CThostFtdcSettlementInfoConfirmField) {
    document();
    get_string(BrokerID);
    get_string(InvestorID);
    get_string(ConfirmDate);
    get_string(ConfirmTime);
    get_int(SettlementID);
    get_string(AccountID);
    get_string(CurrencyID);
    write_document();
}
setter_def(CThostFtdcSpecificInstrumentField) {
    parse_or_throw();
    set_string(InstrumentID);
}
getter_def(CThostFtdcSpecificInstrumentField) {
    document();
    get_string(InstrumentID);
    write_document();
}

setter_def(CThostFtdcTradeField) {
    parse_or_throw();
    set_string(BrokerID);
    set_string(InvestorID);
    set_string(InstrumentID);
    set_string(OrderRef);
    set_string(UserID);
    set_string(ExchangeID);
    set_string(TradeID);
    set_flag(Direction, Direction);
    set_string(OrderSysID);
    set_string(ParticipantID);
    set_string(ClientID);
    set_flag(TradingRole, TradingRole);
    set_string(ExchangeInstID);
    set_flag(OffsetFlag, OffsetFlag);
    set_flag(HedgeFlag, HedgeFlag);
    set_double(Price);
    set_int(Volume);
    set_string(TradeDate);
    set_string(TradeTime);
    set_flag(TradeType, TradeType);
    set_flag(PriceSource, PriceSource);
    set_string(TraderID);
    set_string(OrderLocalID);
    set_string(ClearingPartID);
    set_string(BusinessUnit);
    set_int(SequenceNo);
    set_string(TradingDay);
    set_int(SettlementID);
    set_int(BrokerOrderSeq);
    set_flag(TradeSource, TradeSource);
    set_string(InvestUnitID);
}
getter_def(CThostFtdcTradeField) {
    document();
    get_string(BrokerID);
    get_string(InvestorID);
    get_string(InstrumentID);
    get_string(OrderRef);
    get_string(UserID);
    get_string(ExchangeID);
    get_string(TradeID);
    get_flag(Direction, Direction);
    get_string(OrderSysID);
    get_string(ParticipantID);
    get_string(ClientID);
    get_flag(TradingRole, TradingRole);
    get_string(ExchangeInstID);
    get_flag(OffsetFlag, OffsetFlag);
    get_flag(HedgeFlag, HedgeFlag);
    get_double(Price);
    get_int(Volume);
    get_string(TradeDate);
    get_string(TradeTime);
    get_flag(TradeType, TradeType);
    get_flag(PriceSource, PriceSource);
    get_string(TraderID);
    get_string(OrderLocalID);
    get_string(ClearingPartID);
    get_string(BusinessUnit);
    get_int(SequenceNo);
    get_string(TradingDay);
    get_int(SettlementID);
    get_int(BrokerOrderSeq);
    get_flag(TradeSource, TradeSource);
    get_string(InvestUnitID);
    write_document();
}
setter_def(CThostFtdcTradingAccountField) {
    parse_or_throw();
    set_string(BrokerID);
    set_string(AccountID);
    set_double(PreMortgage);
    set_double(PreCredit);
    set_double(PreDeposit);
    set_double(PreBalance);
    set_double(PreMargin);
    set_double(InterestBase);
    set_double(Interest);
    set_double(Deposit);
    set_double(Withdraw);
    set_double(FrozenMargin);
    set_double(FrozenCash);
    set_double(FrozenCommission);
    set_double(CurrMargin);
    set_double(CashIn);
    set_double(Commission);
    set_double(CloseProfit);
    set_double(PositionProfit);
    set_double(Balance);
    set_double(Available);
    set_double(WithdrawQuota);
    set_double(Reserve);
    set_string(TradingDay);
    set_int(SettlementID);
    set_double(Credit);
    set_double(Mortgage);
    set_double(ExchangeMargin);
    set_double(DeliveryMargin);
    set_double(ExchangeDeliveryMargin);
    set_double(ReserveBalance);
    set_string(CurrencyID);
    set_double(PreFundMortgageIn);
    set_double(PreFundMortgageOut);
    set_double(FundMortgageIn);
    set_double(FundMortgageOut);
    set_double(FundMortgageAvailable);
    set_double(MortgageableFund);
    set_double(SpecProductMargin);
    set_double(SpecProductFrozenMargin);
    set_double(SpecProductCommission);
    set_double(SpecProductFrozenCommission);
    set_double(SpecProductPositionProfit);
    set_double(SpecProductCloseProfit);
    set_double(SpecProductPositionProfitByAlg);
    set_double(SpecProductExchangeMargin);
    set_flag(BizType, BizType);
    set_double(FrozenSwap);
    set_double(RemainSwap);
}
getter_def(CThostFtdcTradingAccountField) {
    document();
    get_string(BrokerID);
    get_string(AccountID);
    get_double(PreMortgage);
    get_double(PreCredit);
    get_double(PreDeposit);
    get_double(PreBalance);
    get_double(PreMargin);
    get_double(InterestBase);
    get_double(Interest);
    get_double(Deposit);
    get_double(Withdraw);
    get_double(FrozenMargin);
    get_double(FrozenCash);
    get_double(FrozenCommission);
    get_double(CurrMargin);
    get_double(CashIn);
    get_double(Commission);
    get_double(CloseProfit);
    get_double(PositionProfit);
    get_double(Balance);
    get_double(Available);
    get_double(WithdrawQuota);
    get_double(Reserve);
    get_string(TradingDay);
    get_int(SettlementID);
    get_double(Credit);
    get_double(Mortgage);
    get_double(ExchangeMargin);
    get_double(DeliveryMargin);
    get_double(ExchangeDeliveryMargin);
    get_double(ReserveBalance);
    get_string(CurrencyID);
    get_double(PreFundMortgageIn);
    get_double(PreFundMortgageOut);
    get_double(FundMortgageIn);
    get_double(FundMortgageOut);
    get_double(FundMortgageAvailable);
    get_double(MortgageableFund);
    get_double(SpecProductMargin);
    get_double(SpecProductFrozenMargin);
    get_double(SpecProductCommission);
    get_double(SpecProductFrozenCommission);
    get_double(SpecProductPositionProfit);
    get_double(SpecProductCloseProfit);
    get_double(SpecProductPositionProfitByAlg);
    get_double(SpecProductExchangeMargin);
    get_flag(BizType, BizType);
    get_double(FrozenSwap);
    get_double(RemainSwap);
    write_document();
}
setter_def(CThostFtdcUserLogoutField) {
    parse_or_throw();
    set_string(BrokerID);
    set_string(UserID);
}
getter_def(CThostFtdcUserLogoutField) {
    document();
    get_string(BrokerID);
    get_string(UserID);
    write_document();
}

#include "structs.h"

getter_def(CThostFtdcConnectField) {
    document();
    write_document();
}

getter_def(CThostFtdcDisconnect) {
    document();
    get_int(Reason);
    write_document();
}

setter_def(CThostFtdcSubMarketDataField) {
    parse_or_throw();
    set_array(InstrumentID, Count);
}

setter_def(CThostFtdcUnsubMarketDataField) {
    parse_or_throw();
    set_array(InstrumentID, Count);
}

// Undef macros.
#include "rjmacro.h"
