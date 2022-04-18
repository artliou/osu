package edu.osu.praterj.geotagger;
import android.provider.BaseColumns;
import android.database.sqlite.SQLiteOpenHelper;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.content.ContentValues;
import android.util.Log;

/**
 * Created by JPrate on 2/22/2018.
 */

public final class geotaggerDBContract {

    private geotaggerDBContract(){};

    public final class geotaggerDBEntries implements BaseColumns {
        public static final String DB_NAME = "geotagger_db";
        public static final String TABLE_NAME = "entries";
        public static final String COLUMN_NAME_ENTRIES_LAT = "entries_lat";
        public static final String COLUMN_NAME_ENTRIES_LONG = "entries_long";
        public static final String COLUMN_NAME_ENTRIES_TEXT = "entries_text";
        public static final int DB_VERSION = 1;

        public static final String SQL_CREATE_ENTRIES_TABLE = "CREATE TABLE " + geotaggerDBEntries.TABLE_NAME +
                "(" + geotaggerDBEntries._ID + " INTEGER PRIMARY KEY NOT NULL, " +
                geotaggerDBEntries.COLUMN_NAME_ENTRIES_LAT + " REAL," +
                geotaggerDBEntries.COLUMN_NAME_ENTRIES_LONG + " REAL," +
                geotaggerDBEntries.COLUMN_NAME_ENTRIES_TEXT + " TEXT);";

        public static final String SQL_DROP_ENTRIES_TABLE = "DROP TABLE IF EXISTS " + geotaggerDBEntries.TABLE_NAME;
    }
}

class geotaggerDB extends SQLiteOpenHelper {

    private String debugTag = "geotagger_db";

    public geotaggerDB(Context context) {
        super(context, geotaggerDBContract.geotaggerDBEntries.DB_NAME, null, geotaggerDBContract.geotaggerDBEntries.DB_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase database) {
        Log.i(debugTag, "Created SQL Database");
        database.execSQL(geotaggerDBContract.geotaggerDBEntries.SQL_CREATE_ENTRIES_TABLE);

        /*ContentValues testMessage = new ContentValues();
        testMessage.put(geotaggerDBContract.geotaggerDBEntries.COLUMN_NAME_ENTRIES_LAT, -44.2);
        testMessage.put(geotaggerDBContract.geotaggerDBEntries.COLUMN_NAME_ENTRIES_LONG, 123.2);
        testMessage.put(geotaggerDBContract.geotaggerDBEntries.COLUMN_NAME_ENTRIES_TEXT, "I am a test");
        database.insert(geotaggerDBContract.geotaggerDBEntries.TABLE_NAME, null,testMessage);*/
    }

    @Override
    public void onUpgrade(SQLiteDatabase database, int oldVersion, int newVersion) {
        Log.i(debugTag, "Data base upgrading... " + oldVersion + "->" + newVersion);
        Clear(database);
    }

    public void Clear(SQLiteDatabase database) {
        Log.i(debugTag, "Resetting Database");
        database.execSQL(geotaggerDBContract.geotaggerDBEntries.SQL_DROP_ENTRIES_TABLE);
        onCreate(database);
    }
}