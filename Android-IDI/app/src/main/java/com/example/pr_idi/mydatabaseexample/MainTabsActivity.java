package com.example.pr_idi.mydatabaseexample;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.TabLayout;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.animation.AccelerateInterpolator;
import android.view.animation.Animation;
import android.view.animation.DecelerateInterpolator;
import android.view.animation.ScaleAnimation;
import android.widget.Toast;

import com.example.pr_idi.mydatabaseexample.fragments.CreateFragment;
import com.example.pr_idi.mydatabaseexample.fragments.ListFragment;
import com.example.pr_idi.mydatabaseexample.services.CoinService;
import com.example.pr_idi.mydatabaseexample.services.CoinServiceImpl;

public class MainTabsActivity extends AppCompatActivity {

    private final CoinService coinService;

    private FloatingActionButton fab;
    private ViewPager mViewPager;
    private Fragment[] mFragments;

    public MainTabsActivity() {
        this.coinService = new CoinServiceImpl(this);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_tabs);

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        mFragments = new Fragment[3];
        final SectionsPagerAdapter mSectionsPagerAdapter = new SectionsPagerAdapter(getSupportFragmentManager());

        mViewPager = (ViewPager) findViewById(R.id.container);
        mViewPager.setAdapter(mSectionsPagerAdapter);

        TabLayout tabLayout = (TabLayout) findViewById(R.id.tabs);
        tabLayout.setupWithViewPager(mViewPager);

        fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onFABClick(v);
            }
        });

        tabLayout.setOnTabSelectedListener(new TabLayout.OnTabSelectedListener() {
            @Override
            public void onTabSelected(TabLayout.Tab tab) {
                mViewPager.setCurrentItem(tab.getPosition());
                Fragment currentFragment = mFragments[mViewPager.getCurrentItem()];
                if (currentFragment instanceof ListFragment) {
                    ((ListFragment) currentFragment).updateInformation();
                }
                changeFABDesign(tab.getPosition());
            }

            @Override
            public void onTabUnselected(TabLayout.Tab tab) {
            }

            @Override
            public void onTabReselected(TabLayout.Tab tab) {

            }
        });

        mViewPager.setCurrentItem(0);
    }

    Boolean exit = Boolean.FALSE;

    @Override
    public void onBackPressed() {
        if (exit) {
            finish();
        } else {
            exit = true;
            Toast.makeText(this, getResources().getString(R.string.back_exit), Toast.LENGTH_SHORT).show();
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    exit = false;
                }
            }, 3000);
        }
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main_tabs, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_settings:
                startActivity(new Intent(this, SettingsActivity.class));
                break;
            case R.id.action_about:
                startActivity(new Intent(this, AboutActivity.class));
                break;
            default:
                return super.onOptionsItemSelected(item);
        }
        return true;
    }

    private class SectionsPagerAdapter extends FragmentPagerAdapter {

        SectionsPagerAdapter(FragmentManager fm) {
            super(fm);
        }

        @Override
        public Fragment getItem(int position) {
            switch (position) {
                case 0:
                    mFragments[0] = ListFragment.newInstance().setCoinService(coinService);
                    return mFragments[0];
                case 1:
                    mFragments[1] = CreateFragment.newInstance().setCoinService(coinService);
                    return mFragments[1];
            }
            return null;
        }

        @Override
        public int getCount() {
            return 2;
        }

        @Override
        public CharSequence getPageTitle(int position) {
            switch (position) {
                case 0:
                    return getResources().getString(R.string.list_tab);
                case 1:
                    return getResources().getString(R.string.create_tab);
            }
            return null;
        }
    }

    public void onFABClick(View view) {
        Fragment fragment = mFragments[mViewPager.getCurrentItem()];
        if (fragment instanceof CreateFragment) {
            ((CreateFragment) fragment).onFABClick(view);
        }
    }

    private void changeFABDesign(final int position) {
        fab.clearAnimation();
        if (position == 0) {
            ScaleAnimation shrink = new ScaleAnimation(1f, 0.2f, 1f, 0.2f,
                    Animation.RELATIVE_TO_SELF, 0.5f,
                    Animation.RELATIVE_TO_SELF, 0.5f);
            shrink.setDuration(150);
            shrink.setInterpolator(new DecelerateInterpolator());
            fab.startAnimation(shrink);
            fab.setVisibility(View.GONE);
        } else {
            ScaleAnimation expand = new ScaleAnimation(0.2f, 1f, 0.2f, 1f,
                    Animation.RELATIVE_TO_SELF, 0.5f,
                    Animation.RELATIVE_TO_SELF, 0.5f);
            expand.setDuration(100);
            expand.setInterpolator(new AccelerateInterpolator());
            fab.startAnimation(expand);
            fab.setVisibility(View.VISIBLE);
        }
    }
}
