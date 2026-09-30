package com.example.pr_idi.mydatabaseexample.utils;

import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.pr_idi.mydatabaseexample.R;
import com.example.pr_idi.mydatabaseexample.persistence.CoinModel;

import java.util.List;

public class CoinListAdapter extends RecyclerView.Adapter<CoinListAdapter.ViewHolder> {

    private final List<CoinModel> coinsData;

    public CoinListAdapter(List<CoinModel> coinsData) {
        this.coinsData = coinsData;
    }

    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_coin, parent, false);
        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {
        CoinModel coin = coinsData.get(position);

        holder.mCoinCurrency.setText(coin.getCurrency());
        holder.mCoinCountry.setText(coin.getCountry());
        holder.mCoinYear.setText(String.valueOf(coin.getYear()));
        holder.mCoinDescription.setText(coin.getDescription());
    }

    @Override
    public int getItemCount() {
        return coinsData.size();
    }

    static class ViewHolder extends RecyclerView.ViewHolder {

        private TextView mCoinCurrency, mCoinCountry, mCoinYear, mCoinDescription;

        ViewHolder(View itemView) {
            super(itemView);
            mCoinCurrency = (TextView) itemView.findViewById(R.id.coin_currency);
            mCoinCountry = (TextView) itemView.findViewById(R.id.coin_country);
            mCoinYear = (TextView) itemView.findViewById(R.id.coin_year);
            mCoinDescription = (TextView) itemView.findViewById(R.id.coin_description);
        }
    }
}
