package com.example.pr_idi.mydatabaseexample;

import android.app.Fragment;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.PreferenceFragment;
import android.support.v7.app.AlertDialog;
import android.widget.Toast;

import com.example.pr_idi.mydatabaseexample.utils.LocaleUtils;

public class SettingsActivity extends PreferenceActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Fragment fragment = new MyPreferenceFragment();
        getFragmentManager().beginTransaction().replace(android.R.id.content, fragment).commit();
    }

    @Override
    public void onBackPressed() {
        Intent intent = new Intent(SettingsActivity.this, MainTabsActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK);
        intent.addFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION);
        startActivity(intent);
    }

    public static class MyPreferenceFragment extends PreferenceFragment {

        Preference language, updateAll, emailButton, gitHubButton;

        @Override
        public void onCreate(final Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            addPreferencesFromResource(R.xml.preferences);

            language = findPreference("language");
            updateAll = findPreference("applicationDataUpdate");
            emailButton = findPreference("emailReport");
            gitHubButton = findPreference("gitHubReport");

            language.setOnPreferenceClickListener(new Preference.OnPreferenceClickListener() {
                @Override
                public boolean onPreferenceClick(Preference preference) {
                    AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
                    builder.setTitle(R.string.nav_language).setItems(R.array.languages_array, new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialogInterface, int which) {
                            LocaleUtils localeUtils = new LocaleUtils(getActivity().getApplicationContext());
                            switch (which) {
                                case 1:
                                    localeUtils.setAndStoreLocale("es");
                                    break;
                                case 2:
                                    localeUtils.setAndStoreLocale("en");
                                    break;
                                default:
                                    localeUtils.setAndStoreLocale("ca");
                            }
                            Toast.makeText(getActivity(), getResources().getString(R.string.new_language), Toast.LENGTH_LONG).show();
                            getActivity().recreate();
                        }
                    });
                    builder.show();
                    return false;
                }
            });

        }

    }

}