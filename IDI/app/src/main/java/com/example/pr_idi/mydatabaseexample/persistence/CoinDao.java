package com.example.pr_idi.mydatabaseexample.persistence;

import java.util.List;

public interface CoinDao {

    void upgradeDB();

    List<CoinModel> getAllCoins();

    void saveCoin(CoinModel coin);

}
