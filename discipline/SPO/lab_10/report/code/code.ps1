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
  $sorted_processes = $($processes | Sort-Object CreationDate -Descending)

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
