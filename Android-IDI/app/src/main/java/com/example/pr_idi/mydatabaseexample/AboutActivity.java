package com.example.pr_idi.mydatabaseexample;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.method.LinkMovementMethod;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

public class AboutActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_about);

        TextView description = (TextView) findViewById(R.id.description);
        TextView version = (TextView) findViewById(R.id.version);
        ImageView backArrow = (ImageView) findViewById(R.id.back);

        description.setClickable(true);
        description.setMovementMethod(LinkMovementMethod.getInstance());

        String versionName = BuildConfig.VERSION_NAME;
        version.setText(versionName);

        backArrow.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });
    }
}
