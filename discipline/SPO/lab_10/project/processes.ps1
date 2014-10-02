<#
.SYNOPSIS
This PowerShell script prints a list of running processes.

.DESCRIPTION
This PowerShell script prints a list of running processes, sorting them by start time.
Color indicates the priority of a process.

.EXAMPLE
.\processes.ps1

.NOTES
Script written by students 120602 group, BSUIR.
#>

Set-Variable MAX_PROCESS_NAME_LENGTH -option Constant -value 40

$processes = Get-WmiObject -Class win32_process
$sorted_processes = $($processes | Sort-Object Priority, CreationDate)

$process_number = 1
$sorted_processes | foreach-object {
    if ($_.CreationDate) {

        $OutputString = [string]$process_number + ". " + $_.Name
        
        $spaces = $MAX_PROCESS_NAME_LENGTH - $($OutputString).Length
        for ($i = 0; $i -le $spaces; $i++) { 
            $OutputString += " "
        }

        $OutputString += "Priority: " + $_.Priority + "`t`t"
        $OutputString += "Start time: " + $_.ConvertToDateTime($_.CreationDate) 
        
        $color = $_.Priority
        Write-Host $OutputString -ForegroundColor $color
        $process_number += 1
    }
}

############## statistics #################

$priority_statistics = @()
$sorted_processes_count = $sorted_processes.GetUpperBound(0)

for ($i = 1; $i -le $sorted_processes_count; $i++) {
    
    $count++;
    if (($sorted_processes[$i].Priority -ne $old_priority)) {
        
        $priority_statistics += $old_priority, $count
        $count = 0
    
    } elseif ($i -eq $sorted_processes_count) {
        $priority_statistics += $old_priority, $($count+1)
    }

    $old_priority = $sorted_processes[$i].Priority
}

$processes_count = $sorted_processes.GetUpperBound(0)
$upperBound = $priority_statistics.GetUpperBound(0)

Write-Host ============ statistics ============
Write-Host Priority num `t Count `t Percentage
Write-Host ------------------------------------
for ($i = 2; $i -lt $upperBound; $i+=2) {
    # round 0.3
    $percent = $($priority_statistics[$i+1] / $processes_count * 100)
    Write-Host Priority "#" $priority_statistics[$i] `t $priority_statistics[$i+1] `t  $percent.ToString("F02")%
}
Write-Host ------------------------------------
