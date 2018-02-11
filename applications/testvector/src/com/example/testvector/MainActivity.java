package com.example.testvector;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Locale;
import java.util.TimeZone;

import android.app.Activity;
import android.content.Context;
import android.media.AudioManager;
import android.os.Bundle;
import android.os.Trace;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;


public class MainActivity extends Activity implements OnClickListener {

    private static final TimeZone AMERICA_LOS_ANGELES = TimeZone.getTimeZone("America/Los_Angeles");
	private static final TimeZone AUSTRALIA_LORD_HOWE = TimeZone.getTimeZone("Australia/Lord_Howe");
	
	private TextView mResultTest1,mResultTest2,mResultTest3,mResultTest4,mResultTest5,mResultTest6;
	private Button mBtnTest1,mBtnTest2,mBtnTest3,mBtnTest4,mBtnTest5,mBtnTest6;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Trace.beginSection("trace begin test vector");
        setRequestedOrientation(9);
        setContentView(R.layout.activity_main);
        mResultTest1 = (TextView) this.findViewById(R.id.textView1);
        mResultTest2 = (TextView) this.findViewById(R.id.textView2);
        mResultTest3 = (TextView) this.findViewById(R.id.textView3);
        mResultTest4 = (TextView) this.findViewById(R.id.textView4);
        mResultTest5 = (TextView) this.findViewById(R.id.textView5);
        mResultTest6 = (TextView) this.findViewById(R.id.textView6);
        mBtnTest1 = (Button) this.findViewById(R.id.button1);
        mBtnTest1.setOnClickListener(this);
        mBtnTest2 = (Button) this.findViewById(R.id.button2);
        mBtnTest2.setOnClickListener(this);
        mBtnTest3 = (Button) this.findViewById(R.id.button3);
        mBtnTest3.setOnClickListener(this);
        mBtnTest4 = (Button) this.findViewById(R.id.button4);
        mBtnTest4.setOnClickListener(this);
        mBtnTest5 = (Button) this.findViewById(R.id.button5);
        mBtnTest5.setOnClickListener(this);
        mBtnTest6 = (Button) this.findViewById(R.id.button6);
        mBtnTest6.setOnClickListener(this);
        Trace.endSection();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

	@Override
	public void onClick(View v) {
		switch(v.getId()) {
		case R.id.button1:
			try {
				testDstZoneWithNonDstTimestampForNonHourDstZone();
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			break;
		case R.id.button2:
			try {
				testNonDstZoneWithDstTimestampForNonHourDstZone();
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			break;
		case R.id.button3:
			try {
				testDstZoneNameWithNonDstTimestamp();
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			break;	
		case R.id.button4:
			try {
				testNonDstZoneNameWithDstTimestamp();
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			break;		
		case R.id.button5:
//			try {
//				printMediaCodecsList();
//			} catch (Exception e) {
//				// TODO Auto-generated catch block
//				e.printStackTrace();
//			}
			break;	
		case R.id.button6:
//				testMusicMute();
			break;	
		default:
			
			break;
		}
	}

	private void testMusicMute() {
		AudioManager audioManager = (AudioManager) this.getSystemService(Context.AUDIO_SERVICE);
		audioManager.adjustStreamVolume(3, AudioManager.ADJUST_MUTE, AudioManager.FLAG_SHOW_UI);
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
//		boolean isMuted = audioManager.isStreamMute(3);
//		mResultTest6.setText(isMuted ? "Muted" : "Unmuted");
	}
	
	private void appendText(TextView tv, String text) {
		Log.d("sakalog", text);
		tv.append(text);
	}
	
	public void printMediaCodecsList() {
		int codecs = android.media.MediaCodecList.getCodecCount();
		appendText(mResultTest5, "Codec Count: " + codecs + "\n");
		for (int i=0; i<codecs; i++) {
			appendText(mResultTest5, "\n");
			android.media.MediaCodecInfo info = android.media.MediaCodecList.getCodecInfoAt(i);
			if (info != null) {
				appendText(mResultTest5, "Codec[" + i + "] Name: " + info.getName() + "\n");
				appendText(mResultTest5, "Codec[" + i + "] Encoder: " + (info.isEncoder() ? "YES" : "NO") + "\n");
				String[] types = info.getSupportedTypes();
				String s = "";
				for (int j=0; j<types.length; j++) {
					if (j > 0) {
						s += ",";
					}
					s += types[j];
				}
				appendText(mResultTest5, "Codec[" + i + "] Supported Types: " + s + "\n");
			}
		}		
	}

    public void testDstZoneWithNonDstTimestampForNonHourDstZone() throws Exception {
        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm zzzz", Locale.US);
        Log.d("FXJ", " 00 TimeZone " + format.getTimeZone());
        format.setTimeZone(AMERICA_LOS_ANGELES);
        Log.d("FXJ", " 001 TimeZone " + format.getTimeZone());
        Calendar calendar = new GregorianCalendar(AUSTRALIA_LORD_HOWE);
        Log.d("FXJ", " 01 TimeZone " + calendar.getTimeZone());
        calendar.setTime(format.parse("2011-06-21T20:00 Lord Howe Daylight Time".toString())); // 9:00 GMT+11
        Log.d("FXJ", " 02 TimeZone " + calendar.getTimeZone());
        //assertEquals(19, calendar.get(Calendar.HOUR_OF_DAY)); // 9:00 GMT+10:30
        //assertEquals(30, calendar.get(Calendar.MINUTE));
        if (mResultTest1 != null) {
        	String str = "Result: hour of day=  " + calendar.get(Calendar.HOUR_OF_DAY) + " minute= " + calendar.get(Calendar.MINUTE);
        	mResultTest1.setText(str);
        }
    }
    
    public void testNonDstZoneWithDstTimestampForNonHourDstZone() throws Exception {
        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm zzzz", Locale.US);
        Log.d("FXJ", " 10 TimeZone " + format.getTimeZone());
        Calendar calendar = new GregorianCalendar(AUSTRALIA_LORD_HOWE);
        Log.d("FXJ", " 11 TimeZone " + calendar.getTimeZone());
        calendar.setTime(format.parse("2010-12-21T19:30 Lord Howe Standard Time")); //9:00 GMT+10:30
        Log.d("FXJ", " 12 TimeZone " + calendar.getTimeZone());
        //assertEquals(20, calendar.get(Calendar.HOUR_OF_DAY)); // 9:00 GMT+11:00
        //assertEquals(0, calendar.get(Calendar.MINUTE));
        if (mResultTest2 != null) {
        	String str = "Result2: hour of day=  " + calendar.get(Calendar.HOUR_OF_DAY) + " minute= " + calendar.get(Calendar.MINUTE);
        	mResultTest2.setText(str);
        }
    }
    
    public void testDstZoneNameWithNonDstTimestamp() throws Exception {
        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm zzzz", Locale.US);
        Log.d("FXJ", " 20 TimeZone " + format.getTimeZone());
        Calendar calendar = new GregorianCalendar(AMERICA_LOS_ANGELES);
        Log.d("FXJ", " 21 TimeZone " + calendar.getTimeZone());
        Date mDate = format.parse("2011-06-21T10:00 Pacific Standard Time");
        Log.d("FXJ", " 210 TimeZone " + mDate);
        calendar.setTime(format.parse("2011-06-21T10:00 Pacific Standard Time")); // 18:00 GMT-8
        Log.d("FXJ", " 22 TimeZone " + calendar.getTimeZone());
        //assertEquals(11, calendar.get(Calendar.HOUR_OF_DAY)); // 18:00 GMT-7
        //assertEquals(0, calendar.get(Calendar.MINUTE));
        if (mResultTest3 != null) {
        	String str = "Result3: hour of day=  " + calendar.get(Calendar.HOUR_OF_DAY) + " minute= " + calendar.get(Calendar.MINUTE);
        	mResultTest3.setText(str);
        }
    }

    public void testNonDstZoneNameWithDstTimestamp() throws Exception {
        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm zzzz", Locale.US);
        Log.d("FXJ", " 30 TimeZone " + format.getTimeZone());
        Calendar calendar = new GregorianCalendar(AMERICA_LOS_ANGELES);
        Log.d("FXJ", " 31 TimeZone " + calendar.getTimeZone());
        calendar.setTime(format.parse("2010-12-21T10:00 Pacific Daylight Time")); // 17:00 GMT-7
        Log.d("FXJ", " 32 TimeZone " + calendar.getTimeZone());
        //assertEquals(9, calendar.get(Calendar.HOUR_OF_DAY)); // 17:00 GMT-8
        //assertEquals(0, calendar.get(Calendar.MINUTE));
        if (mResultTest4 != null) {
        	String str = "Result4: hour of day=  " + calendar.get(Calendar.HOUR_OF_DAY) + " minute= " + calendar.get(Calendar.MINUTE);
        	mResultTest4.setText(str);
        }
    }
}
