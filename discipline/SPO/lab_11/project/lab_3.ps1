Function Collect-Hours ([string] $eventLog, [double[]] $accumulator) {
    Get-Eventlog -Logname $eventLog | Foreach-Object {
	$h = $_.TimeGenerated.Hour
	$accumulator[$h]++
    }
}

Function Normalize-Freq ([double[]] $freq) {
    $total = 0
    ForEach ($val in $freq) { $total += $val }
    For ($i = 0; $i -lt $freq.Length; $i++) { $freq[$i] /= $total }
}

Function Write-Histogram ([double[]] $freq, [int] $bar_width) {
    $max_freq = ($freq | Measure-Object -Max).Maximum
    if ($max_freq -eq 0) { $max_freq = 1 } 

    For ($i = 0; $i -lt $freq.Length; $i++) {
	$cur_start_time = "{0,2}:{1,0}" -f $i, "00"
	$cur_freq = $freq[$i]
	$cur_num_filled = $bar_width * ($cur_freq / $max_freq)

	$cur_bar = "["

	$cur_bar += "#" * $cur_num_filled
	$cur_bar += "-" * ($bar_width - $cur_num_filled)
	$cur_bar += "]"

	$cur_percent = "{0:N2}%" -f ($cur_freq * 100)
	Write-Host "$cur_start_time $cur_bar $cur_percent"
    }
}

$num_hours = 24
[double[]]$freq = ,0 * $num_hours
[string[]]$logs = "system","application","osession","windows powershell"

Foreach ($log in $logs) {
	[double[]]$freq = ,0 * $num_hours
	[string[]]$logs = "system","application","osession","windows powershell"

	Collect-Hours $log $freq
	Normalize-Freq $freq

	Write-Host "$log log statistics:"
	Write-Histogram $freq 40
	Write-Host 
    }
