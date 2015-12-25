package com.android.utils;

import android.content.Context;

import com.panxw.aes.test.SIMUtils;

public class Encryptor {

	private static Encryptor mInstance = null;
	private Context mContext;

	private Encryptor(Context context) {
		this.mContext = context;
	}

	public static Encryptor getInstance(Context context) {
		if (mInstance == null) {
			mInstance = new Encryptor(context);
		}
		return mInstance;
	}

	protected static final String TAG = Encryptor.class.getSimpleName();
	private static final String LIB_NAME = "umc_jni";

	static {
		System.loadLibrary(LIB_NAME);
	}

	public native String desDecrypt(String data);

	public native String desEncrypt(String data);

	public native byte[] aesCrypt(byte[] data, long time, int mode);

	public String getIMEI() {
		return SIMUtils.getInstance(mContext).getDeviceId();
	}

	public String getSignature() {
		String imei = getIMEI();
		if (imei == null || "".equals(imei)) {
			return "67FF8BCD74639574F7766D48CC68E96A";
		}
		return imei;
	}

	public String getTest() {
		return "umc_auth_test";
	}

	/**
	 * 将16进制转换为二进制(服务端)
	 * 
	 * @param hexStr
	 * @return
	 */
	public byte[] hexStr2Bytes(String hexStr) {
		if (hexStr.length() < 1)
			return null;
		byte[] result = new byte[hexStr.length() / 2];
		for (int i = 0; i < hexStr.length() / 2; i++) {
			int high = Integer.parseInt(hexStr.substring(i * 2, i * 2 + 1), 16);
			int low = Integer.parseInt(hexStr.substring(i * 2 + 1, i * 2 + 2),
					16);
			result[i] = (byte) (high * 16 + low);
		}
		return result;
	}

	public String bytes2HexStr(byte[] data) {
		if (data == null || data.length == 0) {
			return null;
		}
		StringBuffer buf = new StringBuffer();
		for (int i = 0; i < data.length; i++) {
			if (((int) data[i] & 0xff) < 0x10) { /* & 0xff转换无符号整型 */
				buf.append("0");
			}
			buf.append(Long.toHexString((int) data[i] & 0xff)); /* 转换16进制,下方法同 */
		}
		return buf.toString();
	}
}
