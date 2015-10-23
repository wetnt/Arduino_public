package bbk.sys.ui;

import bbk.bbk.main.R;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.Toast;

public class BBKLayView {

	// ---------------------------------------------------------------
	protected LinearLayout BBKLay;
	public Activity bbkAct;

	// ------------------------------------------------------------------------------------------

	public void LayoutInt(Context ctx, int res) {
		// ------------------------------------------------------------------------------------------
		bbkAct = (Activity) ctx;
		// ------------------------------------------------------------------------------------------
		BBKLay = (LinearLayout) LayoutInflater.from(bbkAct).inflate(res, null);
		// ------------------------------------------------------------------------------------------
		int w = FrameLayout.LayoutParams.FILL_PARENT;
		int h = FrameLayout.LayoutParams.FILL_PARENT;
		int g = Gravity.TOP | Gravity.LEFT;
		// -----------------------------------------------------------------------
		FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(w, h, g);
		FrameLayout FrameLay = (FrameLayout) bbkAct.findViewById(R.id.FrameLay);
		FrameLay.addView(BBKLay, params);
		// ------------------------------------------------------------------------------------------
	}

	public void layshow(boolean show) {
		// ------------------------------------------------------------------------------------------
		if (show) {
			BBKLay.setVisibility(View.VISIBLE);
		} else {
			BBKLay.setVisibility(View.GONE);
		}
		// ------------------------------------------------------------------------------------------
	}

	public void layshowe() {
		// ------------------------------------------------------------------------------------------
		if (BBKLay.isShown()) {
			BBKLay.setVisibility(View.GONE);
		} else {
			BBKLay.setVisibility(View.VISIBLE);
		}
		// ------------------------------------------------------------------------------------------
	}

	// ====================================================================================
	// ####################################################################################
	// ###############################œ˚œ¢…Ë÷√#############################################
	// ####################################################################################
	// ====================================================================================
	private Toast toast;

	public void toastShow(String str) {
		if (toast == null) {
			toast = Toast.makeText(bbkAct, str, Toast.LENGTH_SHORT);
		} else {
			toast.cancel();
			toast.setText(str);
		}
		toast.show();
		// Toast.makeText(this, str, Toast.LENGTH_SHORT).show();
	}

	// ====================================================================================
	public static void ddd(String str) {
		String s = "=== " + str;
		System.out.println(s);
	}

	public static void ddd(int str) {
		String s = "=== " + str;
		System.out.println(s);
	}

	// ====================================================================================
	public void mmm(String str) {
		// ---------------------------------------------
		new AlertDialog.Builder(bbkAct).setTitle("BBK_BlueTooth").setMessage(str)
				.show();
		// ---------------------------------------------
	}
	// ====================================================================================

}
