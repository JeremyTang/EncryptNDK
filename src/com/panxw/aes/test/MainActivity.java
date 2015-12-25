package com.panxw.aes.test;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;

import com.panxw.aes.jni.R;

public class MainActivity extends Activity implements OnClickListener {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		findViewById(R.id.btn_aes).setOnClickListener(this);
		findViewById(R.id.btn_des).setOnClickListener(this);
		// try {
		// System.out.println("======jni-crypt-test======");
		// byte[] data = TESTDATA.getBytes("UTF-8");
		// data = AESCryptor.crypt(data, System.currentTimeMillis(), 0);
		// String hexStr = AESCryptor.bytes2HexStr(data);
		// System.out.println("encrypt:" + hexStr);
		// SharedPreferences sp = getSharedPreferences("test", MODE_PRIVATE);
		// sp.edit().putString("value", hexStr).commit();
		//
		// data = AESCryptor.hexStr2Bytes(sp.getString("value", ""));
		// data = AESCryptor.crypt(data, System.currentTimeMillis(), 1);
		// System.out.println("decrypt:" + new String(data, "UTF-8"));
		//
		// System.out.println("======java-crypt-test======");
		// data = TESTDATA.getBytes("UTF-8");
		// data = JavaAESCryptor.encrypt(data);
		// hexStr = AESCryptor.bytes2HexStr(data);
		// System.out.println("encrypt:" + hexStr);
		//
		// data = AESCryptor.hexStr2Bytes(hexStr);
		// data = JavaAESCryptor.decrypt(data);
		// System.out.println("decrypt:" + new String(data, "UTF-8"));
		//
		// } catch (UnsupportedEncodingException e) {
		// s
	}

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.btn_aes:
			startActivity(new Intent(this, AESEncryptActivity.class));
			break;
		case R.id.btn_des:
			startActivity(new Intent(this, DESEncryptActivity.class));
			break;
		default:
			break;
		}
	}

}
