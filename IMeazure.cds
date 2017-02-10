<distribution version="13.0.0" name="IMeazure" type="MSI64">
	<prebuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></prebuild>
	<postbuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></postbuild>
	<msi GUID="{0FB33892-5CA4-49B3-8A72-E257A13C6A81}" x64="true">
		<general appName="IMeazure" outputLocation="c:\Users\cnmuser\Desktop\iMeazure_v91_cc\cvidistkit.IMeazure" relOutputLocation="cvidistkit.IMeazure" outputLocationWithVars="c:\Users\cnmuser\Desktop\iMeazure_v91_cc\cvidistkit.%name" relOutputLocationWithVars="cvidistkit.%name" upgradeBehavior="1" autoIncrement="true" version="1.0.1">
			<arp company="Argonne National Laboratory" companyURL="" supportURL="" contact="" phone="" comments="v91"/>
			<summary title="" subject="" keyWords="" comments="" author=""/></general>
		<userinterface language="English" showPaths="true" readMe="" license="">
			<dlgstrings welcomeTitle="IMeazure" welcomeText=""/></userinterface>
		<dirs appDirID="100">
			<installDir name="[Program Files]" dirID="24" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="IMeazure" dirID="100" parentID="24" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="[Start&gt;&gt;Programs]" dirID="7" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="IMeazure" dirID="101" parentID="7" isMSIDir="false" visible="true" unlock="false"/></dirs>
		<files>
			<simpleFile fileID="0" sourcePath="c:\Users\cnmuser\Desktop\iMeazure_v91_cc\cvibuild.iMeazure\Release64\iMeazure.exe" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/></files>
		<fileGroups>
			<projectOutput64 targetType="0" dirID="100" projectID="0">
				<fileID>0</fileID></projectOutput64>
			<projectDependencies64 dirID="100" projectID="0"/></fileGroups>
		<shortcuts>
			<shortcut name="IMeazure" targetFileID="0" destDirID="101" cmdLineArgs="" description="" runStyle="NORMAL"/></shortcuts>
		<mergemodules/>
		<products/>
		<runtimeEngine installToAppDir="false" activeXsup="true" analysis="true" cvirte="true" dotnetsup="true" instrsup="true" lowlevelsup="true" lvrt="true" netvarsup="true" rtutilsup="true">
			<hasSoftDeps/></runtimeEngine><sxsRuntimeEngine>
			<selected>false</selected>
			<doNotAutoSelect>false</doNotAutoSelect></sxsRuntimeEngine>
		<advanced mediaSize="650">
			<launchConditions>
				<condition>MINOS_WINXP_SP0</condition>
			</launchConditions>
			<includeConfigProducts>true</includeConfigProducts>
			<maxImportVisible>silent</maxImportVisible>
			<maxImportMode>merge</maxImportMode>
			<custMsgFlag>false</custMsgFlag>
			<custMsgPath>msgrte.txt</custMsgPath>
			<signExe>false</signExe>
			<certificate></certificate>
			<signTimeURL></signTimeURL>
			<signDescURL></signDescURL></advanced>
		<Projects NumProjects="1">
			<Project000 ProjectID="0" ProjectAbsolutePath="c:\Users\cnmuser\Desktop\iMeazure_v91_cc\iMeazure.prj" ProjectRelativePath="iMeazure.prj"/></Projects>
		<buildData progressBarRate="0.277346050130465">
			<progressTimes>
				<Begin>0.000000000000000</Begin>
				<ProductsAdded>0.206953500000000</ProductsAdded>
				<DPConfigured>1.881953500000000</DPConfigured>
				<DPMergeModulesAdded>4.366953000000001</DPMergeModulesAdded>
				<DPClosed>12.816953500000000</DPClosed>
				<DistributionsCopied>29.142100999999997</DistributionsCopied>
				<End>360.560389999999980</End></progressTimes></buildData>
	</msi>
</distribution>
