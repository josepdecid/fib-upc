package com.example.pr_idi.mydatabaseexample.fragments;

import android.os.Bundle;
import android.support.design.widget.Snackbar;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

import com.example.pr_idi.mydatabaseexample.R;
import com.example.pr_idi.mydatabaseexample.persistence.CoinModel;
import com.example.pr_idi.mydatabaseexample.services.CoinService;

public class CreateFragment extends Fragment {

    private CoinService coinService;

    private EditText mCurrencyInput, mValueInput, mYearInput, mCountryInput, mDescriptionInput;

    public CreateFragment() {
        super();
    }

    public static CreateFragment newInstance() {
        CreateFragment fragment = new CreateFragment();
        Bundle args = new Bundle();
        fragment.setArguments(args);
        return fragment;
    }

    public CreateFragment setCoinService(CoinService coinService) {
        this.coinService = coinService;
        return this;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_create, container, false);
        mCurrencyInput = (EditText) rootView.findViewById(R.id.create_form_currency);
        mValueInput = (EditText) rootView.findViewById(R.id.create_form_value);
        mYearInput = (EditText) rootView.findViewById(R.id.create_form_year);
        mCountryInput = (EditText) rootView.findViewById(R.id.create_form_country);
        mDescriptionInput = (EditText) rootView.findViewById(R.id.create_form_description);
        return rootView;
    }

    @Override
    public void onDetach() {
        super.onDetach();
    }

    public void onFABClick(View view) {
        CoinModel coinModel = new CoinModel();
        coinModel.setCurrency(mCurrencyInput.getText().toString());
        coinModel.setValue(Float.valueOf(mValueInput.getText().toString()));
        coinModel.setYear(Integer.valueOf(mYearInput.getText().toString()));
        coinModel.setCountry(mCountryInput.getText().toString());
        coinModel.setDescription(mDescriptionInput.getText().toString());

        try {
            coinService.saveCoin(coinModel);
            // Afegir llista
            Log.d("[SAVE]", "OKKKKK");
            Snackbar.make(view, getResources().getString(R.string.successful_create_coin), Snackbar.LENGTH_LONG).show();
        } catch (Exception exception) {
            Log.d("[SAVE]", exception.getMessage());
            Snackbar.make(view, exception.getMessage(), Snackbar.LENGTH_LONG).show();
        }
    }

}
