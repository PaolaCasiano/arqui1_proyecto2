package com.example.arquipy2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.UnsupportedEncodingException;
import java.util.HashMap;
import java.util.Map;

public class MainActivity extends AppCompatActivity {
    private RequestQueue rq;
    private Button botonMostrar;
    private Button botonControl;

    private EditText txtCadena;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        rq = Volley.newRequestQueue(this);

        txtCadena = findViewById(R.id.editText2);
        botonMostrar = findViewById(R.id.btnMostrar);
        botonMostrar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String cadena = txtCadena.getText().toString();
                Submit(cadena);
                Toast.makeText(getApplicationContext(),"¡Se agrego cadena a la pila!",Toast.LENGTH_SHORT).show();
                txtCadena.setText("");

            }
        });

        botonControl = findViewById(R.id.btnControl);
        botonControl.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Control();
            }
        });

    }

    private void Submit(final String cadena)
    {
        String url="http://192.168.0.33:8000/guardar_letras?letras="+cadena;
        StringRequest str = new StringRequest(Request.Method.POST, url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        Toast.makeText(getApplicationContext(),response, Toast.LENGTH_SHORT).show();
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Toast.makeText(getApplicationContext(),"Error:"+error.toString(),Toast.LENGTH_LONG).show();
            }
        }) {
            @Override
            protected Map<String,String> getParams(){
                Map<String,String> params = new HashMap<>();
               // params.put("letras", cadena);
                return params;
            }
        };
        rq.add(str);
    }

    private void Control()
    {
        String url="http://192.168.0.33:8000/cambiar_escritorio";
        StringRequest str = new StringRequest(Request.Method.GET, url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        Toast.makeText(getApplicationContext(),response, Toast.LENGTH_SHORT).show();
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Toast.makeText(getApplicationContext(),"Error:"+error.toString(),Toast.LENGTH_LONG).show();
            }
        }) {
            @Override
            protected Map<String,String> getParams(){
                Map<String,String> params = new HashMap<>();
                // params.put("letras", cadena);
                return params;
            }
        };
        rq.add(str);
    }
}
