package edu.osu.praterj.geotagger;

import android.Manifest;
import android.content.ContentValues;
import android.content.Intent;
import android.location.Location;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.support.v4.app.ActivityCompat;
import android.os.Bundle;
import android.content.pm.PackageManager;
import android.util.Log;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.location.LocationListener;
import com.google.android.gms.location.LocationRequest;
import com.google.android.gms.location.LocationServices;

import android.view.View;
import android.widget.ImageView;
import android.widget.SimpleCursorAdapter;
import android.widget.TextView;
import android.widget.ListView;
import android.widget.Button;
import android.widget.EditText;

import edu.osu.praterj.geotagger.geotaggerDBContract;
import edu.osu.praterj.geotagger.geotaggerDB;
import android.database.sqlite.SQLiteDatabase;
import android.database.Cursor;
import android.widget.ResourceCursorAdapter;

public class Geotagger
        extends AppCompatActivity
        implements  GoogleApiClient.ConnectionCallbacks,
                    GoogleApiClient.OnConnectionFailedListener,
                    ActivityCompat.OnRequestPermissionsResultCallback
    {

    static int PERMISSION_LOCATION = 0x100;

    private GoogleApiClient localGoogleApiClient;
    private LocationRequest localLocationRequest;
    private Location localLastLocation;
    private LocationListener localLocationListener;
    private String debugTag = "geotagger_main";
    private double localLat;
    private double localLong;
    private geotaggerDB localDatabase;
    private SQLiteDatabase localSQLDatabase;
    private SimpleCursorAdapter localGeoMsgListAdapter;
    private Cursor localDBCursor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_geotagger);
        if (localGoogleApiClient == null) {
            Log.i (debugTag, "Creating Google Api");
            localGoogleApiClient = new GoogleApiClient.Builder(this,this,this)
                    .addApi(LocationServices.API)
                    .build();
            localGoogleApiClient.connect();
        }

        localLocationRequest = LocationRequest.create();
        localLocationRequest.setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY);
        localLocationRequest.setInterval(1000);
        localLocationRequest.setFastestInterval(1000);
        localLocationListener = new LocationListener() {
            @Override
            public void onLocationChanged(Location location) {
                if (location != null) {
                    updateLocation();
                    Log.i (debugTag, "Location is valid");
                } else {
                    // Location not available :(
                    Log.i (debugTag, "Location is not valid");
                }
            }
        };
        SetDefaultLocation();

        localDatabase = new geotaggerDB(this);
        localSQLDatabase = localDatabase.getWritableDatabase();

        Button addGeoMsg = findViewById(R.id.addGeoMsg);
        addGeoMsg.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                EditText msgText = findViewById(R.id.editText);
                ContentValues newGeoMessage = new ContentValues();
                newGeoMessage .put(geotaggerDBContract.geotaggerDBEntries.COLUMN_NAME_ENTRIES_LAT, localLat);
                newGeoMessage .put(geotaggerDBContract.geotaggerDBEntries.COLUMN_NAME_ENTRIES_LONG, localLong);
                newGeoMessage .put(geotaggerDBContract.geotaggerDBEntries.COLUMN_NAME_ENTRIES_TEXT, msgText.getText().toString());
                localSQLDatabase.insert(geotaggerDBContract.geotaggerDBEntries.TABLE_NAME, null, newGeoMessage );
                UpdateGeoMsgListView();
            }
        });

        Button clearGeoMsg = findViewById(R.id.geoMsgClear);
        clearGeoMsg.setOnClickListener(new View.OnClickListener() {
           @Override
           public void onClick(View v) {
               localDatabase.Clear(localSQLDatabase);
               UpdateGeoMsgListView();
           }
        });
        UpdateGeoMsgListView();
    }

    private void SetDefaultLocation() {
        localLat = 44.5;
        localLong = -123.2;
        Log.i (debugTag, "Location Defaulted   Lat: " + localLat + "    Long: " + localLong);
        ImageView gpsEnabled = (ImageView) findViewById(R.id.gpsEnabled);
        ImageView gpsDisabled = (ImageView) findViewById(R.id.gpsDisabled);
        gpsEnabled.setVisibility(ImageView.INVISIBLE);
        gpsDisabled.setVisibility(ImageView.VISIBLE);
        UpdateLocationText();
    }

    @Override
    protected void onStart() {
        Log.i (debugTag, "Activity start");
        localGoogleApiClient.connect();
        super.onStart();
    }

    @Override
    protected void onStop() {
        Log.i (debugTag, "Activity stop");
        localGoogleApiClient.disconnect();
        super.onStop();
    }

    @Override
    public void onConnected(@Nullable Bundle bundle) {
        // onconnect
        Log.i (debugTag, "Activity connected");

        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED)
        {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission.ACCESS_COARSE_LOCATION}, PERMISSION_LOCATION);
            // Show some error stuff since we are rejected
            Log.i (debugTag, "No Location permissions");
            return;
        }
        updateLocation();
    }

    @Override
    public void onConnectionFailed(ConnectionResult result) {
        Log.w(debugTag, result.toString());
    }

    @Override
    public void onConnectionSuspended(int data) {
        Log.i(debugTag, "Connection Suspended :" + data);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions,
                                    @NonNull int[] grantResults) {
        if (requestCode == PERMISSION_LOCATION)
        {
            if (grantResults.length > 0)
            {
                updateLocation();
            }
        }
    }

    private void updateLocation() {
        Log.i (debugTag, "Updating Location");
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            Log.w (debugTag, "No Location permissions");
            SetDefaultLocation();
            return;
        }

        // Update location
        LocationServices.FusedLocationApi.requestLocationUpdates(localGoogleApiClient, localLocationRequest, localLocationListener);
        localLastLocation = LocationServices.FusedLocationApi.getLastLocation(localGoogleApiClient);

        if (localLastLocation != null) {
            // update location :)
            localLat = localLastLocation.getLatitude();
            localLong = localLastLocation.getLongitude();
            Log.i (debugTag, "Location Updated   Lat: " + localLat + "    Long: " + localLong);
            ImageView gpsEnabled = (ImageView) findViewById(R.id.gpsEnabled);
            ImageView gpsDisabled = (ImageView) findViewById(R.id.gpsDisabled);
            gpsDisabled.setVisibility(ImageView.INVISIBLE);
            gpsEnabled.setVisibility(ImageView.VISIBLE);
            UpdateLocationText();
        }
    }

    private void UpdateLocationText() {
        TextView realLat = (TextView) findViewById(R.id.textRealLat);
        TextView realLong = (TextView) findViewById(R.id.textRealLong);
        realLat.setText(Double.toString(localLat));
        realLong.setText(Double.toString(localLong));
    }

    private void UpdateGeoMsgListView() {
        Log.i(debugTag, "Updating List View");
        localDBCursor = localSQLDatabase.query(
                geotaggerDBContract.geotaggerDBEntries.TABLE_NAME,
                new String[]{
                        geotaggerDBContract.geotaggerDBEntries._ID,
                        geotaggerDBContract.geotaggerDBEntries.COLUMN_NAME_ENTRIES_LAT,
                        geotaggerDBContract.geotaggerDBEntries.COLUMN_NAME_ENTRIES_LONG,
                        geotaggerDBContract.geotaggerDBEntries.COLUMN_NAME_ENTRIES_TEXT
                },
                null,
                null,
                null,
                null,
                null);
        ListView geoMsgListView = findViewById(R.id.msgList);
        localGeoMsgListAdapter = new SimpleCursorAdapter(
                this,
                R.layout.geomsglayout,
                localDBCursor,
                new String[]{
                        geotaggerDBContract.geotaggerDBEntries.COLUMN_NAME_ENTRIES_LAT,
                        geotaggerDBContract.geotaggerDBEntries.COLUMN_NAME_ENTRIES_LONG,
                        geotaggerDBContract.geotaggerDBEntries.COLUMN_NAME_ENTRIES_TEXT
                },
                new int[]{
                    R.id.textRealLat, R.id.textRealLong, R.id.textGeoMsgText
                },
                0);
        geoMsgListView.setAdapter(localGeoMsgListAdapter);
    }
}
