package com.example.testvector;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.util.Log;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

public class ButtonSwitch extends LinearLayout {
	private final String TAG = ButtonSwitch.class.getSimpleName();
	private TypedArray mAttrs;
	private Context mContext;
	private int mDistance;
	private ImageView mIconView;
	private int mImageSize;
	private Drawable mSelectedSrc;
	private Drawable mSrc;
	private boolean mState;
	private String mText;
	private int mTextColor;
	private int mTextSelectedColor;
	private int mTextSize;
	private TextView mTextView;
	private boolean mUseDefAttrs;

	public ButtonSwitch(Context context, AttributeSet attrs) {
		this(context, attrs, 0);
	}

	public ButtonSwitch(Context context, AttributeSet attrs, int defStyleAttr) {
		super(context, attrs, defStyleAttr);

		this.mContext = context;
		setOrientation(LinearLayout.HORIZONTAL);
		setGravity(16);

		android.util.Log.d(TAG, "AttributeSet: " + attrs);
		TypedArray a = mContext.obtainStyledAttributes(attrs, R.styleable.ButtonSwitch);
		android.util.Log.d(TAG, "TypedArray: " + a + " length " + a.length());

		this.mDistance = a.getDimensionPixelSize(R.styleable.ButtonSwitch_distance, mContext.getResources().getDimensionPixelSize(
						R.dimen.button_switch_def_distance));

		this.mSrc = a.getDrawable(R.styleable.ButtonSwitch_icon);
		android.util.Log.d(TAG, "mSrc: " + mSrc + " order: " + R.styleable.ButtonSwitch_icon);
		mSrc = mContext.getResources().getDrawable(R.drawable.icon_data_close);
		
		this.mSelectedSrc = a.getDrawable(R.styleable.ButtonSwitch_icon_selected);
		mSelectedSrc = mContext.getResources().getDrawable(R.drawable.icon_data_open);
		android.util.Log.d(TAG, "mSelectedSrc: " + mSelectedSrc);

		this.mImageSize = a.getDimensionPixelSize(
				R.styleable.ButtonSwitch_icon_size,
				this.mContext.getResources().getDimensionPixelSize(
						R.dimen.button_switch_def_image_size));
		this.mState = a.getBoolean(R.styleable.ButtonSwitch_status, true);

		//this.mText = mContext.getResources().getString(a.getInt(R.styleable.ButtonSwitch_text, R.string.wifi));
		mText = a.getString(R.styleable.ButtonSwitch_text);
		// mText = mContext.getString(R.string.mobile_data);
		android.util.Log.d(TAG, "mText: " + mText);

		this.mTextColor = a.getColor(R.styleable.ButtonSwitch_text_color,
				mContext.getResources().getColor(R.color.button_switch_text));
		this.mTextSelectedColor = a.getColor(R.styleable.ButtonSwitch_text_color_selected, this.mContext.getResources().getColor(
						R.color.button_switch_text_selected));
		this.mTextSize = a.getDimensionPixelSize(R.styleable.ButtonSwitch_text_size, this.mContext.getResources().getDimensionPixelSize(
						R.dimen.button_switch_def_text_size));
		a.recycle();

		// initAttrs(paramContext.obtainStyledAttributes(paramAttributeSet,
		// R.styleable.ButtonSwitch));
		// init();

		addChildView();
		initShowUI();
	}
	
    private void addChildView() {
        this.mIconView = new ImageView(this.mContext);
        this.mIconView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
        LinearLayout.LayoutParams localLayoutParams = new LinearLayout.LayoutParams(this.mImageSize, this.mImageSize);
        localLayoutParams.setMarginEnd(this.mDistance);
        this.mIconView.setLayoutParams(localLayoutParams);
        addView(this.mIconView);
        this.mTextView = new TextView(this.mContext);
        this.mTextView.setText(this.mText);
        this.mTextView.setTextSize(this.mTextSize);
        this.mTextView.setGravity(16);
        addView(this.mTextView);
    }

    private void initShowUI() {
        setState(this.mState, true);
    }

    private void setIconViewState(boolean paramBoolean) {
        if (this.mIconView == null) {
            Log.d(this.TAG, "setIconViewState: mIconView == null,I don't know what happened!");
            return;
        }
        mIconView.setImageDrawable(paramBoolean ? mSelectedSrc : mSrc);
    }

    private void setState(boolean paramBoolean1, boolean paramBoolean2) {
        if ((!paramBoolean2) && (this.mState == paramBoolean1)) {
            Log.i(this.TAG, "setState: mState = state,state disChange.method useless,return.");
            return;
        }
        setIconViewState(paramBoolean1);
        setTextViewState(paramBoolean1);
        this.mState = paramBoolean1;
    }

    private void setTextViewState(boolean paramBoolean) {
        if (this.mTextView == null) {
            Log.i(this.TAG, "setTextViewState: mTextView == null,I don't know what happened!");
            return;
        }
        mTextView.setTextColor(paramBoolean ? mTextSelectedColor : mTextColor);
    }

    public boolean getStatus() {
        return this.mState;
    }

    public void setState(boolean paramBoolean) {
        setState(paramBoolean, false);
    }

    public void setmSrc(Drawable mSrc) {
        this.mSrc = mSrc;
    }

    public void setmSelectedSrc(Drawable mSelectedSrc) {
        this.mSelectedSrc = mSelectedSrc;
    }

    public void setmText(String mText) {
        this.mText = mText;
    }

}
