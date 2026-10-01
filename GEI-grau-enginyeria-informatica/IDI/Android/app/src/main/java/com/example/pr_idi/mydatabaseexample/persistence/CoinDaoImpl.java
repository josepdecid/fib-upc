package com.example.pr_idi.mydatabaseexample.persistence;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import java.util.ArrayList;
import java.util.List;

public class CoinDaoImpl extends SQLiteOpenHelper implements CoinDao {

    private static final String TABLE_COINS = "coins";
    private static final String COLUMN_ID = "_id";
    private static final String COLUMN_CURRENCY = "currency";
    private static final String COLUMN_VALUE = "value";
    private static final String COLUMN_YEAR = "year";
    private static final String COLUMN_COUNTRY = "country";
    private static final String COLUMN_DESCRIPTION = "description";

    private static final String DATABASE_NAME = "coins.db";
    private static final int DATABASE_VERSION = 1;

    private static final String DATABASE_CREATE = "create table " + TABLE_COINS + "( "
            + COLUMN_ID + " integer primary key autoincrement, "
            + COLUMN_CURRENCY + " text not null, "
            + COLUMN_VALUE + " real not null, "
            + COLUMN_YEAR + " integer, "
            + COLUMN_COUNTRY + " text not null, "
            + COLUMN_DESCRIPTION + " text"
            + ");";

    public CoinDaoImpl(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase database) {
        database.execSQL(DATABASE_CREATE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_COINS);
        onCreate(db);
    }


    @Override
    public void upgradeDB() {
        SQLiteDatabase database = this.getWritableDatabase();
        onUpgrade(database, 1, 2);
        database.close();
    }

    @Override
    public List<CoinModel> getAllCoins() {
        SQLiteDatabase database = this.getWritableDatabase();

        List<CoinModel> coins = new ArrayList<>();
        String[] columns = {COLUMN_CURRENCY, COLUMN_VALUE, COLUMN_YEAR, COLUMN_DESCRIPTION};
        Cursor cursor = database.query(TABLE_COINS, columns, null, null, null, null, null);

        cursor.moveToFirst();
        while (!cursor.isAfterLast()) {
            coins.add(coinMapper(cursor));
            cursor.moveToNext();
        }

        cursor.close();
        database.close();
        return coins;
    }

    @Override
    public void saveCoin(CoinModel coin) {
        SQLiteDatabase database = this.getWritableDatabase();

        ContentValues values = new ContentValues();
        values.put(COLUMN_CURRENCY, coin.getCurrency());
        values.put(COLUMN_VALUE, coin.getValue());
        values.put(COLUMN_COUNTRY, coin.getCountry());
        values.put(COLUMN_YEAR, coin.getYear());
        values.put(COLUMN_DESCRIPTION, coin.getDescription());

        database.insert(TABLE_COINS, null, values);
        database.close();
    }

    private CoinModel coinMapper(Cursor cursor) {
        CoinModel coin = new CoinModel();
        coin.setCurrency(cursor.getString(1));
        coin.setValue(cursor.getFloat(2));
        coin.setYear(cursor.getInt(3));
        //coin.setCountry(cursor.getString(4));
        //coin.setDescription(cursor.getString(5));
        return coin;
    }
}
