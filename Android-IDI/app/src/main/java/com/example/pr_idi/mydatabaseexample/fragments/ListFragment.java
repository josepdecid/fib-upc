package com.example.pr_idi.mydatabaseexample.fragments;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.example.pr_idi.mydatabaseexample.R;
import com.example.pr_idi.mydatabaseexample.persistence.CoinModel;
import com.example.pr_idi.mydatabaseexample.services.CoinService;
import com.example.pr_idi.mydatabaseexample.utils.CoinListAdapter;

import java.util.ArrayList;
import java.util.List;

public class ListFragment extends Fragment {

    private CoinService coinService;
    private RecyclerView mRecyclerView;

    private List<CoinModel> mData = new ArrayList<>();

    public static ListFragment newInstance() {
        ListFragment fragment = new ListFragment();
        Bundle args = new Bundle();
        fragment.setArguments(args);
        return fragment;
    }

    public ListFragment setCoinService(CoinService coinService) {
        this.coinService = coinService;
        mData = this.coinService.listCoins();
        return this;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_list, container, false);

        mRecyclerView = (RecyclerView) rootView.findViewById(R.id.coin_list_recycler_view);
        mRecyclerView.setLayoutManager(new LinearLayoutManager(getActivity(), LinearLayoutManager.VERTICAL, false));
        mRecyclerView.setAdapter(new CoinListAdapter(mData));
        return rootView;
    }

    @Override
    public void onDetach() {
        super.onDetach();
    }

    public void updateInformation() {
        mData = coinService.listCoins();
        // TODO: invalidate del adapter, refrescar tot es molt guarro!
        mRecyclerView.setAdapter(new CoinListAdapter(mData));
    }

}
