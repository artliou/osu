package edu.osu.praterj.coolpix;

import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import android.content.SharedPreferences;

import net.openid.appauth.AuthState;
import net.openid.appauth.AuthorizationException;
import net.openid.appauth.AuthorizationResponse;
import net.openid.appauth.AuthorizationService;
import net.openid.appauth.AuthorizationService.TokenResponseCallback;
import net.openid.appauth.TokenResponse;

public class AuthCompleteActivity extends AppCompatActivity {

    private AuthorizationService localAuthorizationService;
    private final String debugTag = "Auth Service";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.i(debugTag, "Requesting new auth state");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_auth_complete);

        localAuthorizationService = new AuthorizationService(this);
        AuthorizationResponse authResponse = AuthorizationResponse.fromIntent(getIntent());
        AuthorizationException authException = AuthorizationException.fromIntent(getIntent());

        if (authResponse != null) {
            final AuthState localAuthState = new AuthState(authResponse, authException);
            localAuthorizationService.performTokenRequest(authResponse.createTokenExchangeRequest(),
                    new TokenResponseCallback() {
                        @Override
                        public void onTokenRequestCompleted(@Nullable TokenResponse tokenResponse, @Nullable AuthorizationException exception) {
                            if (exception != null) {
                                Log.i(debugTag, "Auth Failed " + exception.toString());
                            }
                            localAuthState.update(tokenResponse, exception);
                            SharedPreferences authPreferences = getSharedPreferences("auth", MODE_PRIVATE);
                            String authString = localAuthState.jsonSerializeString();
                            Log.i(debugTag, "Auth String "+ authString);
                            authPreferences.edit().putString("state", authString).apply();
                            finish();
                        }
                    });
        }
    }
}
