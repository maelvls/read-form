# Dump the form values from a PDF

A small tool for fetching form content from a PDF.

```sh
$ brew install poppler
$ make
$ ./read_form_fields form.pdf
FieldType: Choice
FieldName: Favourite Colour List Box
FieldStateOption: Black
FieldStateOption: Brown
FieldStateOption: Red
FieldStateOption: Orange
FieldStateOption: Yellow
FieldStateOption: Green
FieldStateOption: Blue
FieldStateOption: Violet
FieldStateOption: Grey
FieldStateOption: White
---
FieldType: Button
FieldName: Language 5 Check Box
FieldValue: Off
FieldStateOption: Off
FieldStateOption: Yes
---
FieldType: Button
FieldName: Language 4 Check Box
FieldValue: Off
FieldStateOption: Off
FieldStateOption: Yes
---
FieldType: Button
FieldName: Language 3 Check Box
FieldValue: Off
FieldStateOption: Off
FieldStateOption: Yes
---
FieldType: Button
FieldName: Language 2 Check Box
FieldValue: Yes
FieldStateOption: Off
FieldStateOption: Yes
---
FieldType: Button
FieldName: Language 1 Check Box
FieldValue: Off
FieldStateOption: Off
FieldStateOption: Yes
---
FieldType: Button
FieldName: Driving License Check Box
FieldValue: Off
FieldStateOption: Off
FieldStateOption: Yes
---
FieldType: Text
FieldName: Height Formatted Field
FieldValue: 150
FieldMaxLength: 20
---
FieldType: Choice
FieldName: Gender List Box
FieldStateOption: Man
FieldStateOption: Woman
---
FieldType: Choice
FieldName: Country Combo Box
FieldStateOption: Austria
FieldStateOption: Belgium
FieldStateOption: Britain
FieldStateOption: Bulgaria
FieldStateOption: Croatia
FieldStateOption: Cyprus
FieldStateOption: Czech-Republic
FieldStateOption: Denmark
FieldStateOption: Estonia
FieldStateOption: Finland
FieldStateOption: France
FieldStateOption: Germany
FieldStateOption: Greece
FieldStateOption: Hungary
FieldStateOption: Ireland
FieldStateOption: Italy
FieldStateOption: Latvia
FieldStateOption: Lithuania
FieldStateOption: Luxembourg
FieldStateOption: Malta
FieldStateOption: Netherlands
FieldStateOption: Poland
FieldStateOption: Portugal
FieldStateOption: Romania
FieldStateOption: Slovakia
FieldStateOption: Slovenia
FieldStateOption: Spain
FieldStateOption: Sweden
---
FieldType: Text
FieldName: City Text Box
FieldValue:
FieldMaxLength: 40
---
FieldType: Text
FieldName: Postcode Text Box
FieldValue:
FieldMaxLength: 20
---
FieldType: Text
FieldName: Address 2 Text Box
FieldValue: adzazd
FieldMaxLength: 40
---
FieldType: Text
FieldName: House nr Text Box
FieldValue:
FieldMaxLength: 20
---
FieldType: Text
FieldName: Address 1 Text Box
FieldValue: azdad
FieldMaxLength: 40
---
FieldType: Text
FieldName: Family Name Text Box
FieldValue: azdzad
FieldMaxLength: 40
---
FieldType: Text
FieldName: Given Name Text Box
FieldValue: dzadazd
FieldMaxLength: 40
```