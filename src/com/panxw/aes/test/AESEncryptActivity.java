package com.panxw.aes.test;

import java.io.UnsupportedEncodingException;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.android.utils.Encryptor;
import com.panxw.aes.jni.R;

public class AESEncryptActivity extends Activity implements OnClickListener {

	private String passwd;
	private EditText mShowEdit;
	private Button encryptBtn, decryptBtn;
	private int tag = 0;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_aes);
		passwd = Constant.AES_DATA;
		mShowEdit = (EditText) findViewById(R.id.edit_encrypt);
		decryptBtn = (Button) findViewById(R.id.btn_decrypt);
		decryptBtn.setOnClickListener(this);
		encryptBtn = (Button) findViewById(R.id.btn_encrypt);
		encryptBtn.setOnClickListener(this);
	}

	protected String encrypt(String string) {
		try {
			byte[] data = string.getBytes("UTF-8");
			data = Encryptor.getInstance(this).aesCrypt(data,
					System.currentTimeMillis(), 0);
			String hexStr = Encryptor.getInstance(this).bytes2HexStr(data);
			return hexStr;
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		return "";
	}

	protected String decrypt(String hexStr) {
		try {
			byte[] data = Encryptor.getInstance(this).hexStr2Bytes(hexStr);
			data = Encryptor.getInstance(this).aesCrypt(data,
					System.currentTimeMillis(), 1);
			return new String(data, "UTF-8");
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		return "";
	}

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.btn_decrypt:
			if (tag > 0) {
				passwd = decrypt(passwd);
				mShowEdit.setText(passwd);
				tag--;
			} else {
				Toast.makeText(this, "数据未加密过！", Toast.LENGTH_SHORT).show();
			}
			break;
		case R.id.btn_encrypt:
			tag++;
			passwd = encrypt(passwd);
			mShowEdit.setText(passwd);
			break;
		default:
			break;
		}
	}

}
