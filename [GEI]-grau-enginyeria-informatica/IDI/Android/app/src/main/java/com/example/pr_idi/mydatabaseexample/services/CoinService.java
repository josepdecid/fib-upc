package com.example.pr_idi.mydatabaseexample.services;

import com.example.pr_idi.mydatabaseexample.persistence.CoinModel;

import java.util.List;

public interface CoinService {

    void upgradeDB();

    List<CoinModel> listCoins();

    void saveCoin(CoinModel coin);
}
