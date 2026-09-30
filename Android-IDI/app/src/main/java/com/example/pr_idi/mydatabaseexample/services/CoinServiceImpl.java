package com.example.pr_idi.mydatabaseexample.services;

import android.content.Context;

import com.example.pr_idi.mydatabaseexample.persistence.CoinDao;
import com.example.pr_idi.mydatabaseexample.persistence.CoinDaoImpl;
import com.example.pr_idi.mydatabaseexample.persistence.CoinModel;

import java.util.List;

public class CoinServiceImpl implements CoinService {

    private final CoinDao coinDao;

    public CoinServiceImpl(Context context) {
        this.coinDao = new CoinDaoImpl(context);
    }

    @Override
    public void upgradeDB() {
        coinDao.upgradeDB();
    }

    @Override
    public List<CoinModel> listCoins() {
        return coinDao.getAllCoins();
    }

    @Override
    public void saveCoin(CoinModel coin) {
        validateFields(coin);
        coinDao.saveCoin(coin);
    }

    private void validateFields(CoinModel coin) {

    }
}
