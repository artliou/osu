package edu.osu.praterj.coolpix;

import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.content.Intent;
import android.app.PendingIntent;
import android.net.Uri;
import android.util.Log;
import android.widget.SimpleAdapter;
import android.widget.ListView;
import android.widget.EditText;

import java.util.HashMap;
import java.util.Map;
import java.util.List;
import java.util.ArrayList;

import android.content.SharedPreferences;
import android.view.View;

import org.json.JSONException;
import org.json.JSONObject;
import org.json.JSONArray;

import net.openid.appauth.AuthState;
import net.openid.appauth.AuthorizationException;
import net.openid.appauth.AuthorizationServiceConfiguration;
import net.openid.appauth.AuthorizationRequest;
import net.openid.appauth.AuthorizationService;
import net.openid.appauth.ResponseTypeValues;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.HttpUrl;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

//
// OAuth2 Client ID
//
// 397564378096-17aeefr098viu7u701prsql3ra7r8d54.apps.googleusercontent.com
//
public class CoolPixActivity extends AppCompatActivity {

    private AuthorizationService localAuthorizationService;
    private AuthState localAuthState;

    final private String debugTag = "CoolPix";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        SharedPreferences authPreferences = getSharedPreferences("auth", MODE_PRIVATE);
        setContentView(R.layout.activity_cool_pix);
        localAuthorizationService = new AuthorizationService(this);
        findViewById(R.id.postButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                localAuthState.performActionWithFreshTokens(localAuthorizationService, new AuthState.AuthStateAction() {
                    @Override
                    public void execute(@Nullable String accessToken, @Nullable String idToken, @Nullable AuthorizationException error) {
                        if (error == null) {
                            OkHttpClient httpClient = new OkHttpClient();
                            HttpUrl reqUrl = HttpUrl.parse("https://www.googleapis.com/plusDomains/v1/people/me/activities");
                            Log.i(debugTag, "Access Token : " + accessToken);
                            String payload = "{'access': {'domainRestricted': true,'items': [{'displayName': 'domain','id': 'domain','type': 'domain'}]},'verb': 'post','object': {'originalContent': '" + ((EditText)findViewById(R.id.postText)).getText().toString() + "'}}";
                            MediaType JSON = MediaType.parse("application/json");

                            RequestBody body = RequestBody.create(JSON, payload);
                            Log.i(debugTag, "payload " + payload);

                            Request request = new Request.Builder()
                                    .url(reqUrl)
                                    .addHeader("Authorization", "Bearer " + accessToken)
                                    .post(body)
                                    .build();
                            httpClient.newCall(request).enqueue(new Callback() {
                                @Override
                                public void onFailure(Call call, IOException e) {
                                    e.printStackTrace();
                                }

                                @Override
                                public void onResponse(Call call, Response response) throws IOException {
                                    Log.i(debugTag, response.body().string());
                                    updateMyPosts();
                                }
                            });
                        }
                    }
                });
            }
        });
        findViewById(R.id.updateButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                updateMyPosts();
            }
        });

    }

    @Override
    protected void onStart() {
        localAuthState = getOrCreateAuthState();
        super.onStart();
    }


    void updateMyPosts() {
        localAuthState.performActionWithFreshTokens(localAuthorizationService, new AuthState.AuthStateAction() {
            @Override
            public void execute(@Nullable String accessToken, @Nullable String idToken, @Nullable AuthorizationException error) {
                if (error == null) {
                    OkHttpClient httpClient = new OkHttpClient();
                    HttpUrl reqUrl = HttpUrl.parse("https://www.googleapis.com/plusDomains/v1/people/me/activities/user");
                    Log.i(debugTag, "Access Token : " + accessToken);
                    Request request = new Request.Builder()
                            .url(reqUrl)
                            .addHeader("Authorization", "Bearer " + accessToken)
                            .build();
                    httpClient.newCall(request).enqueue(new Callback() {
                        @Override
                        public void onFailure(Call call, IOException e) {
                            e.printStackTrace();
                        }`

                        @Override
                        public void onResponse(Call call, Response response) throws IOException {
                            String resp = response.body().string();
                            try {
                                JSONObject jsonObject = new JSONObject(resp);
                                JSONArray itemArray = jsonObject.getJSONArray("items");
                                List<Map<String, String>> posts = new ArrayList<Map<String, String>>();

                                for (int i = 0; i < Math.min(itemArray.length(), 3); i++) {
                                    HashMap<String, String> hashMap = new HashMap<String, String>();
                                    hashMap.put("published", itemArray.getJSONObject(i).getString("published"));
                                    hashMap.put("title", itemArray.getJSONObject(i).getString("title"));
                                    posts.add(hashMap);
                                }

                                final SimpleAdapter postAdapter = new SimpleAdapter(
                                        CoolPixActivity.this,
                                        posts,
                                        R.layout.posts_layout,
                                        new String[]{"published", "title"},
                                        new int[]{R.id.post_publised, R.id.post_title});
                                runOnUiThread(new Runnable() {
                                    @Override
                                    public void run() {
                                        ((ListView) findViewById(R.id.messageList)).setAdapter(postAdapter);
                                    }
                                });

                            } catch (JSONException error) {
                                error.printStackTrace();
                            }
                        }
                    });

                } else {
                    Log.e(debugTag, "Auth error " + error.toString());
                }
            }
        });
    }
    AuthState getOrCreateAuthState() {
        Log.i(debugTag, "Entering getOrCreateAuthState");
        AuthState state = null;
        SharedPreferences authPreferences = getSharedPreferences("auth", MODE_PRIVATE);
        String authState = authPreferences.getString("state", null);
        if (authState != null) {
            try {
                Log.i(debugTag, "auth State" + authState);
                state = localAuthState.jsonDeserialize(authState);
            } catch (JSONException error) {
                error.printStackTrace();
                return null;
            }
        }

        if ((state != null) && (state.getAccessToken() != null)) {
            Log.i(debugTag, "Valid AuthState");
            return state;
        } else {
            Log.i(debugTag, "Updating AuthState");
            updateAuthState();
            return null;
        }
    }

    void updateAuthState() {
        Log.i(debugTag, "Entered updateAuthState");

        Uri authEndpoint = new Uri.Builder().scheme("https").authority("accounts.google.com").path("/o/oauth2/v2/auth").build();
        Uri tokenEndpoint = new Uri.Builder().scheme("https").authority("www.googleapis.com").path("/oauth2/v4/token").build();
        Uri redirect = new Uri.Builder().scheme("edu.osu.praterj.coolpix").path("user").build();

        AuthorizationServiceConfiguration config = new AuthorizationServiceConfiguration(authEndpoint, tokenEndpoint, null);
        AuthorizationRequest req = new AuthorizationRequest.Builder(
                config,
                "397564378096-17aeefr098viu7u701prsql3ra7r8d54.apps.googleusercontent.com",
                ResponseTypeValues.CODE,
                redirect)
                .setScopes("https://www.googleapis.com/auth/plus.me", "https://www.googleapis.com/auth/plus.stream.write", "https://www.googleapis.com/auth/plus.stream.read")
                .build();

        Intent authComplete = new Intent(this, AuthCompleteActivity.class);
        localAuthorizationService.performAuthorizationRequest(req, PendingIntent.getActivity(this, req.hashCode(), authComplete, 0));
    }
}
