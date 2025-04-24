# Run Powershell in hidden window

RunPsScript.exe small windows utility program for running powershell scripts
silently (i.e. without a console window popping up). You could use this for
places where the console window always pops up by default. For example You
could use this to create right click menu automation in regedit
([see example](https://gist.github.com/etcetra7n/569ee8a34eb773e5de917f653f921e0a))

## Usage

```powershell
RunPsScript [whatever_string]
```

The above command will simply **silently** run

```powershell
powershell [whatever_string]
```

For example `RunPsScript "-File 'run.ps1' -ExecutionPolicy Bypass"` will run
`poweshell -File 'run.ps1' -ExecutionPolicy Bypass` silently

**Note**: Note that only one string argument should be passed to RunPsScript