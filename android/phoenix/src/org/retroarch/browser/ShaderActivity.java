package org.retroarch.browser;

import java.io.File;

import android.os.Bundle;

public final class ShaderActivity extends DirectoryActivity {
	@Override
	public void onCreate(Bundle savedInstanceState) {
		File shaderDir = new File(getBaseContext().getApplicationInfo().dataDir, "shaders_glsl");
		if (shaderDir.exists())
			super.setStartDirectory(shaderDir.getAbsolutePath());
		
		super.addAllowedExt(".glsl");
		super.setPathSettingKey("video_shader");
		super.onCreate(savedInstanceState);
	}
}
